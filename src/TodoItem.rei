type todo = {
  id: int,
  title: string,
  completed: bool,
};

let component:
  ReasonReact.componentSpec(
    ReasonReact.stateless,
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );

let make:
  (
    ~todo: todo,
    ~onDelete: unit => unit,
    ~onCompletedToggle: unit => unit,
    'a
  ) =>
  ReasonReact.componentSpec(
    ReasonReact.stateless,
    ReasonReact.stateless,
    ReasonReact.noRetainedProps,
    ReasonReact.noRetainedProps,
    ReasonReact.actionless,
  );
