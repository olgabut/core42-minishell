1️⃣ Prompt & Interactive Mode
minishell$ _


Expected:

Prompt appears

Waiting for input

After each command → new prompt

2️⃣ History (↑ ↓)
ls
pwd
echo hello


Expected:

↑ shows echo hello

↑↑ shows pwd

↓ returns forward

3️⃣ Executables (PATH / absolute / relative)
PATH search
ls
grep main minishell.c
wc -l minishell.c

Absolute path
/bin/ls
/usr/bin/env

Relative path
./a.out
./minishell

Errors
nosuchcommand
./nosuchfile

4️⃣ Arguments
echo hello world
ls -l -a
grep main minishell.c

5️⃣ Quotes
Single quotes ' (no expansion)
echo 'hello world'
echo '$HOME'
echo '| < >'

Double quotes " (allow $)
echo "hello world"
echo "$HOME"
echo "user is $USER"

Mixed
echo "'$USER'"
echo '"$USER"'
echo "'hello' world"

6️⃣ Environment variables $VAR
echo $HOME
echo $PATH
echo $USER


Undefined variable:

echo $NOSUCHVAR

7️⃣ Exit status $?
ls
echo $?

nosuchcommand
echo $?

false
echo $?

8️⃣ Redirections
Output >
echo hello > file.txt
ls > out.txt

Append >>
echo hello >> file.txt
echo world >> file.txt

Input <
cat < file.txt
wc -l < file.txt

Combined
cat < file.txt > out.txt
grep hello < file.txt > result.txt

9️⃣ Heredoc <<
cat << EOF
hello
world
EOF


With pipe:

cat << END | wc -l
one
two
three
END


Expected:

Stops on delimiter

Input not saved in history

🔟 Pipes |
Basic
ls | wc -l
ps aux | grep root

Multiple pipes
cat file.txt | grep hello | wc -l

Builtins in pipe
echo hello | wc -c
env | grep PATH

1️⃣1️⃣ Pipes + Redirections
ls | grep minishell > out.txt
cat < file.txt | grep hello >> result.txt

1️⃣2️⃣ Built-in Commands
echo
echo hello
echo -n hello
echo -n hello world

cd
cd /
cd ..
cd .
cd src
cd /usr/bin


Errors:

cd
cd nosuchdir

pwd
pwd

export
export TEST=42
export USER_NAME=alex
export PATH=/bin:/usr/bin


Check:

env
echo $TEST

unset
unset TEST
unset USER_NAME

env
env

exit
exit
exit 0
exit 1

1️⃣3️⃣ Signals
ctrl-C
sleep 10
# press ctrl-C


Expected:

New line

New prompt

No shell exit

ctrl-D
# press ctrl-D on empty prompt


Expected:

Shell exits

ctrl-\
sleep 10
# press ctrl-\


Expected:

Nothing happens

1️⃣4️⃣ Invalid / Ignored Cases (Allowed)
;
\


Unclosed quotes:

echo "hello
echo 'hello


Expected:

Error or ignore

No crash

1️⃣5️⃣ Edge Cases (Important for Evaluation)
echo ""
echo ''
echo "   "
echo "$"
echo "$USER$HOME"
echo "$?$?"