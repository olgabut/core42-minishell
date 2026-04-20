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
| `` (\n) | prev_exit_code | Nothing |
| `  `(spaces) | 258 ? | Nothing |
| **Quotes** |||
| `echo 'hello world'` | 0 | `hello world`|
| `echo '$HOME'` | 0 | `$HOME`|
| `echo 'a b'` | 0 | `a b` |
| `echo "Hello world"`| 0 | `Hello world`|
| `echo "$HOME"` | 0 | Path |
| `echo "a b" | 0 | `a b` |
| `echo Hi"abc$USER"tadaaam` | 0 | Hiabcobutolintadaaam |
| `echo Hi"abc'$USER'"tadaaam` | 0 | Hiabc'obutolin'tadaaam |
| `echo Hi'abc"$USER"'tadaaam` | 0 | Hiabc"$USER"tadaaam |
| **Errors** |||
| `no_cmd` | 127 | `minishell: no_cmd: command not found` |
| `./no_prog` | 127 | `minishell: ./no_prog: No such file or directory` |
| `\| echo ` | 258 | Pipe can't be first<br/>`minishell: syntax error near unexpected token '\|'` |
| `echo \| \| wc` | 258 | Several pipes can't be located one after another.<br/>`minishell: syntax error near unexpected token '\|'`
| `ls >` | 258 | After redirect should be TOKEN_WORD<br/>`minishell: syntax error near unexpected token 'newline'` |
| `ls << < eof` | 258 | After redirect should be TOKEN_WORD<br/>`minishell: syntax error near unexpected token '<'` |
| `&&` | 258 | `minishell: the command contains unsupported characters` |
| `||` | 258 | `minishell: the command contains unsupported characters` |
| `;` | 258 | `minishell: the command contains unsupported characters` |
| `(` | 258 | `minishell: the command contains unsupported characters` |
| `)` | 258 | `minishell: the command contains unsupported characters` |
| `&` | 258 | `minishell: the command contains unsupported characters` |
| `;;` | 258 | `minishell: the command contains unsupported characters` |
| **Environment variables** |||
| `echo $HOME` | 0 | Path |
| `echo $USER` | 0 | User name |
| `echo $NOT_EXIST` | 0 | Empty line |
| `echo "$HOME"` | 0 | Path |
| `echo '$HOME'` | 0 | `$HOME` |
| **Exit status** |||
| `ls`<br/>`echo $?` | 0 | `0` |
| `invalid`<br/>`echo $?`| ≠0 | Not 0 |
| **Pipes** |||
| `ls \| cat` | 0 | List of files of the current directory in a column |
| `ls \| grep .c` | 0 | Filtered list of files |
| `cat Makefile \| wc -l` | 0 | Count lins in file Makefile<br/>`122` |
| **Redirections** |||
| `echo hello > file` | 0 | Put `hello` in file |
| `echo hi >> file` | 0 | Add `hi` in file |
| `ls > out.txt` | 0 | List of files in file out.txt |
| `cat < file` | 0 | file output |
| `wc -l < file` | 0 | Count lins |
| `cat < no_file`| 1 | `minishell: no_file: No such file or directory` |
| `cat << EOF` | 0 | Input until EOF |
| `cat << EOF \| wc -l` | 0 | Count lines until EOF |
| `<< EOF` | 0 | Nothing |
| **Built in command - echo** |||
| `echo -n hello` | 0 | `hello` without \n |
| `echo -nnnn hi` | 0 | `hi` without \n |
| **Built in command - cd (should update $PWD and $OLDPWD)** |||
| `cd ..` | 0 | Go up |
| `cd /` | 0 | Go to rood directory |
| `cd ~` | 0 | Go HOME (/home/<username>) |
| `cd` | 0 | Go HOME (/home/<username>) |
| `cd -` | 0 | Go to directory before |
| `cd arg1 arg2` | 1 | `minishell: cd: too many arguments` |
| `cd invalid` | 1 | `minishell: cd: invalid: No such file or directory` |
| **Built in command - pwd** |||
| `pwd` | 0 | Path |
| `pwd arg1` | 0 | Path |
| **Built in command - export** |||
| `export` | 0 | All sorted environment variables |
| `export A` | 0 | Add $A (chack using `export` cmd) |
| `export B=2` | 0 | Add $B="2" |
| `export B=3` | 0 | Change $B="3" |
| `export C=abc D=def` | 0 | Add 2 varuables |
| `echo $A` | 0 | Empty line ($A=null)
| `echo $B` | 0 | `3` |
| **Built in command - unset** |||
| `unset` | 0 | No changes |
| `unset D` | 0 | Delete $D variable (chack using `export` or `env` cmd) |
| `echo $D` | 0 | Empty line (no $D) |
| `unset A B` | 0 | Delete 2 variables |
| `unset H C` | 0 | Delete $C, $H does not exist |
| **Built in command - env** |||
| `env` | 0 | All environment variables |
| `env arg1` | 1 | `minishell: env: too many arguments` (!minishell behaviour) |
| **Built in command - exit** |||
| `exit` | last_exit_code | `exit` Exit minishell |
| `exit 42` | 42 | `exit` Exit minishell |
| `exit 1 2` | last_exit_code | `exit`<br/>`minishell: exit: too many arguments` |
| `exit abc` | 255? | `exit`<br/>`minishell: exit: numeric argument required` Exit minishell |
| **PATH** |||
| `echo $PATH` | 0 | Path |
| `unset PATH` | 0 | No $PATH |
| `ls` | 127 | `minishell: ls: command not found` |
| `echo hi` | 0 | All built in commands should work |
| **Signals** |||
| Ctrl+D | | Exit minishell |
| readline has text + Ctrl+C | 130 | New line |
| `sleep 4` + Ctrl+C | 130 | New line |
| `cat` + Ctrl+C | 130 | New line |
| `cat << EOF`<br/>`abc` + Ctrl+C | 130 | New line (!Leaks in readline)|








