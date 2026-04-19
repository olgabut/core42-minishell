# Minishell project

## Plan

* lexer (tokens)
* parser
* heredoc_handler
* executor
* builtins
* env
* signals


### Redirections
*  `<`    = TOKEN_REDIR_IN
*  `>`    = TOKEN_REDIR_OUT
*  `<<`   = TOKEN_HEREDOC,
*  `>>`   = TOKEN_APPEND

### Pipes
`|`

### Built in commands:
* echo with option -n
* cd with only a relative or absolute path
* pwd with no options
* export with no options
* unset with no options
* env with no options or arguments
* exit with no options

# Tests

## Simple command
| Command | Code_exit | Result |
|:------- | :-------- | :----- |
| `ls` | 0 | List of files of the current directory |
| `/bin/ls` | 0 | List of files of the current directory |
| `pwd` | 0 | Absolute path of the current directory |
| `echo hello` | 0 | `hello`|
| `echo hello world` | 0 | `hello world`|
| `echo` | 0 | Empty line |
| `./a.out` | 127 | `minishell: ./a.out: No such file or directory` |
| `./philo` | 0 | Result of ./philo |
| `invalidcmd` | 127 | `minishell: invalidcmd: command not found`|
| **Arguments** | ||
| `ls -l`| 0 | List of files (detailed description) |
| `echo a b c`| 0 | `a b c` |
| `cat file1 file2` | 0 | Output of two files |
| `cat file1 file2` | 1 | <br/>`cat: f1: No such file or directory`|
| `grep main *.c` | 0 | no bonus `grep: *.c: No such file or directory` <br/> with bonus `int     main(int argc, char **argv, char **envp)` |
| **Spaces and empty input** | | |
| `` (\n) | 0 | 


## Arguments
| Command | Code_exit | Result |
|:------- | :-------- | :----- |
| ls -l | 0 | Detailed list |




