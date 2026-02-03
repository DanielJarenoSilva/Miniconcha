_This project has been created as part of the 42 curriculum by djareno | pabalvar_

# Description


**Minishell** is a simple Unix shell written in C, developed as part of the 42 curriculum.  
The objective of this project is to reproduce the basic behavior of **bash** and to gain a better understanding of how a shell works internally.

The shell reads user input, parses commands, and executes them using system calls. It supports command execution with arguments, environment variables, redirections, and pipes. Minishell also implements a set of built-in commands and handles signals according to the project requirements.

This project focuses on fundamental concepts of system programming such as process creation, file descriptor management, signal handling, and command parsing.

## Instructions

This section explains how to compile, run, and use the minishell program.

#### Requirements

The project must be compiled and executed on a Unix-based system.

Required tools:
- GNU Make
- CC compiler
- Standard C libraries

---

#### Makefile

The project includes a Makefile to simplify compilation and cleaning tasks.

Available rules:

- `make`  
  Compiles the source files and generates the `minishell` executable.

- `make clean`  
  Removes all object (`.o`) files generated during compilation.

- `make fclean`  
  Removes object files and the `minishell` executable.

- `make re`  
  Recompiles the project by running `fclean` followed by `make`.

---
#### Usage

Run the shell whith:

`./minishell`

You can then execute commands as you would in bash.

---

#### Built-in Commands

The minishell implements the following builtins:

- `echo`  
  - Supports -n.

- `cd`  
  - Changes the current working directory.

- `pwd`  
  - Prints the current working directory.

- `export`  
  - Sets enviroment variables.

- `unset`  
  - Removes enviroment variables.

- `env`  
  - Displays enviroment variables.

- `exit`  
  - Exits the shell with the appropiate status.


---

#### Pipes

- Supports *pipes(|)* to chain multiple commands.

- The standard output of one command is used as the standard input of the next

---

#### Redirections

The minishell handles the following redirections:

- `<`  
  - Redirects input from a file.
- `>`  
  - Redirects output to a file (overwrite mode).
- `>>`  
  - Redirects output to a file (append mode).
- `<<` (Heredoc)  
  - Reads input until delimiter is found.
  - Variable expansion is disabled when the delimiter is quoted.

---

#### Enviroment Variables

- Expands enviroment variables using `$`.

- Supports `$?` (last command exit status).

- Handles undefined variables correctly. 

---

#### Quotes

- Supports *single quotes* `'`:  
  - Content is interpreted literally.
- Supports *double quotes* `"`:  
  - Allows enviroment variable expansion.
- Correct handling of mixed quoted strings.

#### Signals

- `Ctrl-C`  
  - Interrupts the current command and displays a new prompt.
- `Ctrl-D`  
  - Exits the minishell.
- `CAtrl-\`  
  - Does nothing (same behaviour as bash).

---

# Resources

We used [this page](https://brennan.io/2015/01/16/write-a-shell-in-c/) as a guide.

And we used ChatGPT to find errors