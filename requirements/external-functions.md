# External functions:

## readline
```C
// char *readline (const char *prompt);
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *rl;
	rl = readline("Prompt > ");
	printf("%s\n", rl);
	return (0);
}
```
The function `readline` prints a prompt and return string from the shell.


## fork
```C
// pid_t fork(void);
#include <unistd.h>
#include <sys/types.h>
pid_t pid;
pid = fork();
```
The function `fork` creates a new process by duplicating the calling process.
The new process is referred to as the child process.
The calling process is referred to as the parent process.
https://www.csl.mtu.edu/cs4411.ck/www/NOTES/process/fork/create.html


## wait, waitpid, wait3, wait4
```C
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
pid_t wait(int *_Nullable wstatus);
pid_t waitpid(pid_t pid, int *_Nullable wstatus, int options);
pid_t wait3(int *status, int options, struct rusage *rusage);
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);

```
The function `wait` system call suspends execution of the calling thread
until one of its children terminates.
The function `waitpid` system call suspends execution of the calling thread
until a child specified by pid argument has changed state.
The function `wait3` and the function `wait4` system calls, additionally return resource usage information about the child in the structure pointed to by rusage.


## execve
```C
#include <unistd.h>
int execve(const char *path, char *const _Nullable argv[],
	char *const _Nullable envp[]);
```
The fuction `execve` executes the program referred to by path.


## pipe
```C
#include <unistd.h>
int pipe(int pipefd[2]);
```
The function `pipe` creates a pipe, a unidirectional data channel that can be
used for interprocess communication.


rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, ,
dup, dup2, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs


dup, dup2

signal, sigaction

readline, add_history

open, close

unlink