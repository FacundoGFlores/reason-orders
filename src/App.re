[%bs.raw {|require('./App.css')|}];

type item = {
  id: int,
  name: string,
  unitPrice: float,
};

type state = {items: list(item)};

let component = ReasonReact.reducerComponent("App");

let make = (~message, _children) => {
  ...component,
  initialState: () => {
    items: [
      {id: 1, name: "pizza", unitPrice: 8.0},
      {id: 2, name: "burger", unitPrice: 10.5},
      {id: 1, name: "pasta", unitPrice: 12.0},
    ],
  },
  reducer: ((), _) => ReasonReact.NoUpdate,
  render: self => {
    let numItems = List.length(self.state.items);
    <div className="App">
      <div className="App-header">
        <h2> (ReasonReact.string(message)) </h2>
      </div>
      <div className="App-intro">
        <h3> (ReasonReact.string("Here we put the orders")) </h3>
      </div>
      <div className="footer">
        (ReasonReact.string(string_of_int(numItems) ++ " items"))
      </div>
    </div>;
  },
};