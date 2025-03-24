# Minishell

A simple Unix shell implementation for 42 School.

## Project Structure

The project is organized as follows:

### Core Components
- `main.c`: Entry point and main shell loop
- `includes/minishell.h`: Main header file with all declarations

### Directories
- `builtins/`: Built-in shell commands (cd, echo, export, etc.)
- `command/`: Command structure management
- `exec/`: Command execution and pipeline handling
  - `env_utils.c`: Environment variable management
  - `command_execution.c`: Single command execution
  - `pipeline_execution.c`: Pipeline execution
  - `path_utils.c`: Command path resolution
  - `builtin_execution.c`: Built-in command execution
- `expand/`: Environment variable expansion
- `parse/`: Input parsing
- `redirection/`: I/O redirection handling
- `signals/`: Signal handling
  - `signal_handlers.c`: Signal handler functions
  - `signal_setup.c`: Signal setup functions
- `token/`: Tokenization of input
- `utils/`: Various utility functions

## Features
- Command execution
- Pipelines
- Redirections (>, <, >>, <<)
- Environment variables
- Signal handling (Ctrl+C, Ctrl+\, Ctrl+D)
- Built-in commands (cd, echo, pwd, export, unset, env, exit)
- Quote handling (single and double quotes)

## Compilation
```
make
```

## Usage
```
./minishell
```


fix redirects

test the heredocs more througoutly

refactor functions that are more than 25 lines

refactor files that are more than 5 functions

refactor functions that have more than 5 variables 

