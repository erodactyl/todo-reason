type todo = {
  id: int,
  title: string,
  completed: bool,
};

let component = ReasonReact.statelessComponent("Todo");

let make = (~todo, ~onDelete, ~onCompletedToggle, _children) => {
  ...component,
  render: _ =>
    <div key={string_of_int(todo.id)}>
      <span> {ReasonReact.string(todo.title)} </span>
      <button onClick={_ => onDelete()}>
        {ReasonReact.string("Delete")}
      </button>
      <input
        type_="checkbox"
        checked={todo.completed}
        onChange={_ => onCompletedToggle()}
      />
      {todo.completed ? ReasonReact.string("Completed") : ReasonReact.null}
    </div>,
};
