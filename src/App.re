open TodoItem;

type state = {
  todos: list(TodoItem.todo),
  value: string,
};

type action =
  | AddTodo
  | DeleteTodo(int)
  | ChangeValue(string)
  | ToggleCompleted(int);

let component = ReasonReact.reducerComponent("TodoList");

let make = _children => {
  let handleKeyPress = (e, {ReasonReact.send}) =>
    if (e->ReactEvent.Keyboard.charCode === 13) {
      send(AddTodo);
    };
  {
    ...component,

    initialState: () => {todos: [], value: ""},

    reducer: (action, state) =>
      switch (action) {
      | ChangeValue(value) => ReasonReact.Update({...state, value})
      | AddTodo =>
        if (state.value !== "") {
          ReasonReact.Update({
            todos: [
              {id: Random.int(64000), title: state.value, completed: false},
              ...state.todos,
            ],
            value: "",
          });
        } else {
          ReasonReact.NoUpdate;
        }
      | DeleteTodo(id) =>
        ReasonReact.Update({
          ...state,
          todos: List.filter(todo => todo.id !== id, state.todos),
        })
      | ToggleCompleted(id) =>
        ReasonReact.Update({
          ...state,
          todos:
            List.map(
              todo =>
                todo.id === id ? {...todo, completed: !todo.completed} : todo,
              state.todos,
            ),
        })
      },

    render: self =>
      <div>
        <input
          value={self.state.value}
          onChange={e =>
            self.send(ChangeValue(e->ReactEvent.Form.target##value))
          }
          onKeyPress={self.handle(handleKeyPress)}
          placeholder="Todo value"
        />
        <button onClick={_ => self.send(AddTodo)}>
          {ReasonReact.string("Add todo")}
        </button>
        {ReasonReact.array(
           Array.of_list(
             List.map(
               todo =>
                 <TodoItem
                   key={string_of_int(todo.id)}
                   todo
                   onDelete={_ => self.send(DeleteTodo(todo.id))}
                   onCompletedToggle={_ =>
                     self.send(ToggleCompleted(todo.id))
                   }
                 />,
               self.state.todos,
             ),
           ),
         )}
      </div>,
  };
};
