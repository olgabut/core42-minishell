_This project has been created as part of the 42 curriculum by obutolin, dprikhod._

# Description
In this project, we created a program called **minishell**. It is a simple version of a Unix shell.

Our main goal was to understand how a shell works. We wanted to learn how to read user input, process commands, and execute them in the system.

The program can run basic commands, work with environment variables, and support built-in commands like `cd`, `echo`, `pwd`, `export`, `env`, `unset`, and `exit`. It also handles pipes, redirections, and signals.

This project helped us understand processes, pipes, memory management, and how Unix systems work.

## Parts of the project
The project is divided into several parts.

First, we have the **lexer**. It reads the input line using `readline()` and splits it into tokens. It also checks for syntax errors, supports quotes and special symbols, and saves the history of entered commands using `add_history()`.

Then, we have the **parser**. It takes tokens and builds command structures. It processes pipes and redirections and prepares data for execution. It also expands environment variables.

After that, we have the **executor**. It runs the commands. For external commands, we create child processes using `fork()` and run programs with `execve()`. We use `pipe()` to connect commands and `dup2()` to handle input and output redirections.

We also have **built-in commands** like `cd`, `echo`, `pwd`, `export`, `env`, `unset`, and `exit`. These commands run inside the shell without creating a new process. They change the shell state directly.

There is a module for **environment variables**. It stores variables, updates them, and converts them to an array for execution.

We also implemented **signal handling**. The shell correctly reacts to signals `SIGINT` (Ctrl+C) and `SIGQUIT`(Ctrl+\\). It does not close the shell and handles input in a safe way.

In this project, we used our own library called **libft**. It helped us with basic functions for strings, memory, and lists. This made our code cleaner and easier to manage.


# Instructions
## Compilation

To build the project, simply run:
```bash
make
```
This will compile the minishell executable using the default debug mode, which enables additional debugging flags (-g, AddressSanitizer, and UndefinedBehaviorSanitizer).

You can also explicitly control the build mode:
```bash
#Debug mode (default):
make MODE=debug

#Release mode (without debug flags):
make MODE=release
```

## Execution
After compilation, run the shell with:
```bash
./minishell
```

## Cleaning
Remove object files:
```bash
make clean
```

Remove all generated files (including executables):
```bash
make fclean
```

Rebuild everything:
```bash
make re
```


# Resources

## Documentation and Articles
* [Readline library](https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005fcatch_005fsignals)
* [Pipes in C](https://tldp.org/LDP/lpg/node11.html)
* [How do I use execve in C](https://jameshfisher.com/2017/02/05/how-do-i-use-execve-in-c/)

## Videos
* [Unix Processes in C](https://www.youtube.com/playlist?list=PLfqABt5AS4FkW5mOn2Tn9ZZLLDwA3kZUY)
* [Using execve in C](https://www.youtube.com/watch?v=iq7puCxsgHQ)
* [How to make readline() Exit on Ctrl+C in C programming](https://www.youtube.com/watch?v=dnnH04Zl02s)

## AI
We also used AI tools to help us during the project. We used AI for:
* understand how best to divide the project into smaller parts
* explaining difficult concepts (like pipes, processes, and signals)
* helping us understand errors and debug our code

We did not use AI to fully generate the project. We wrote the logic by ourselves and used AI only as a support tool to learn and fix problems.
