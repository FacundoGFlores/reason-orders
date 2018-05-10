[%bs.raw {|require('./App.css')|}];

type item = {
  id: int,
  name: string,
  price: float,
};

type state = {items: list(item)};

type action =
  | ViewItem(item);

let getPrice = (i: item) => i.price;

let summarize = (l: list(item)) =>
  switch (l) {
  | [] => 0.0
  | l => List.fold_left((x, y) => x +. getPrice(y), 0.0, l)
  };

let handleClick = (onViewItem, item, _e) => onViewItem(item);

module ListItem = {
  let component = ReasonReact.statelessComponent("ListItem");
  let make = (~item, ~onViewItem, _children) => {
    ...component,
    render: _ =>
      <tr className="item" onClick=(handleClick(onViewItem, item))>
        <td> (ReasonReact.string(item.name)) </td>
        <td> (ReasonReact.string(string_of_float(item.price))) </td>
      </tr>,
  };
};

module ListTable = {
  let component = ReasonReact.statelessComponent("ListTable");
  let make = (~items, ~onViewItem, _children) => {
    ...component,
    render: _ =>
      <table className="items">
        <tbody>
          <tr>
            <td> (ReasonReact.string("Food")) </td>
            <td> (ReasonReact.string("Price")) </td>
          </tr>
          (
            items
            |> List.map(item =>
                 <ListItem
                   key=(string_of_int(item.id))
                   item
                   onViewItem
                 />
               )
            |> Array.of_list
            |> ReasonReact.array
          )
          <tr>
            <td> (ReasonReact.string("Total")) </td>
            <td>
              (ReasonReact.string(string_of_float(summarize(items))))
            </td>
          </tr>
        </tbody>
      </table>,
  };
};

let component = ReasonReact.reducerComponent("App");

let make = (~message, _children) => {
  ...component,
  initialState: () => {
    items: [
      {id: 1, name: "pizza", price: 8.0},
      {id: 2, name: "burger", price: 10.5},
      {id: 3, name: "pasta", price: 12.0},
    ],
  },
  reducer: (action, {items}) =>
    switch (action) {
    | ViewItem(item) =>
      Js.log("selected id" ++ string_of_int(item.id));
      ReasonReact.Update({items: items});
    },
  render: self => {
    let numItems = List.length(self.state.items);
    <div className="App">
      <div className="App-header">
        <h2> (ReasonReact.string(message)) </h2>
      </div>
      <div className="App-body">
        <ListTable
          items=self.state.items
          onViewItem=(item => self.send(ViewItem(item)))
        />
      </div>
      <div className="App-footer">
        (ReasonReact.string(string_of_int(numItems) ++ " items"))
      </div>
    </div>;
  },
};