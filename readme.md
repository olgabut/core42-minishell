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
| ls | 0 | List of files of the current directory |
| /bin/ls | 0 | List of files of the current directory |
| pwd | 0 | Absolute path of the current directory |
| echo hello | 0 | `hello`|
| echo hello world | 0 | `hello world`|
| echo | 0 | Empty line |
| ./a.out | 127 | `minishell: ./a.out: No such file or directory` |


