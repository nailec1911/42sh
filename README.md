# 42sh

## The project
The 42sh is one of our year-end project, it's goal is to recreate a Unix SHELL in C with the standard library.<br>
Our reference shell was [tcsh](https://en.wikipedia.org/wiki/Tcsh), but we have deviated from it on certain point.
As this project have a lot of option, we choose to promote line execution over scripting.


## Features
* Handling the execution line, notably the simple and double quotes
* Pipes and multi-pipes
* Magic quotes (try putting "echo \`ls\`" in bash / zsh / tcsh)
* Redirections (>, >>, <, <<)
* Separators ';', '&&' and '||'
* Commands "built-in" : env, cd, echo, exit, alias, unalias, history, setenv, unsetenv, fg, which
* Globing : *, [], ?, ~
* Environement variables, with set, unset, and substitution ($ and ${} in the command-line)
* Alias handling (placed in the file /home/.cache/.42shrc)
* History (placed in the file /home/.cache/.42shhistory) and substitution ('!' in the command line)
* Nice prompt (with last return status, user, pwd and git branch name)
* job control (ctrl-c, ctrl-z, fg)
* line edition (arrow handling, suppr, backspace, ctrl-l, zsh-like autocompletion)

## How to use the project
* Clone the project
```
git clone git@github.com:nailec1911/42sh.git 42sh
```
* Go into the folder (`cd 42sh`)
* Compile the project
```
make re ; make clean
```
* Launch the shell
```
./42sh
```
* Enjoy !

## How to use the Makefile
You can use it to compil the code, and some other things with the following rules:

| Command          | Result                                          |
| ---------------- | ----------------------------------------------- |
| `make`           | Builds a ```42sh``` executable.          |
| `make clean`     | Cleans build dumps, keeping the executable.     |
| `make fclean`    | Removes all of the files created by the build.  |
| `make debug`    | Compile with `-ggdb3` flag if you need to debug the program.  |
| `make tests_run`    | Execute the criterion tests.  |
| `make re`        | Calls `make fclean` and then `make`.            |

## Authors
* [Célian Lombardot](https://github.com/nailec1911)
* [Théophile Combes](https://github.com/Zetsumeii)
* [Adam](https://github.com/adamdelacheisserie)
* [Marius Marolleau](https://github.com/Ciikorrr)
* [Maxime Castet](https://github.com/ctsmax)

---

## More details
* This project is finished since 11/05/2023, 19:42
* The history and alias files are only loaded and updated the 42sh is launched in tty (so not during the tests)
