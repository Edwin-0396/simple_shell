# **Simple_Shell** :shell:

## Description :scroll:

In this project we are tasked with creating our own simple UNIX command interpreter. The program must have the exact same output as sh (/bin/sh) as well as the exact same error output.

### Invocation

Usage: **hsh**[filename]

To invocate **hsh**, compile all **.c** files in the repository and run the resulting executable:

~~~
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
./hsh
~~~

**hsh** can be invoked both interactively an non-interactively. If **hsh** is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Example:

~~~
$ echo "echo 'hello'"| ./hsh
'hello'
$
~~~

If **hsh** is invoked with standard input connected to a terminal (determined by **isatty(3)**), an interactive shell is opened. When executing interactively, **hsh** display de prompt **$** when it is ready to read a command.

### Enviroment :evergreen_tree:

Upon invocation, **hsh** receives and copies the environment of the parent process in which it was executed.

This environment is an array of name-value strings describing variables in the format NAME=VALUE. A few key environmental variables are:

**HOME**
The home directory of the current user and the default directory argument for the cd builtin command.

~~~
$ echo "echo $HOME" | ./hsh
/home/edwin
~~~


**PWD**
The current working directory as set by the cd command.

~~~
$ echo "echo $PWD" | ./hsh
/home/edwin/simple_shell
~~~

**PATH**
A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directory.

~~~
$ echo "echo $PATH" | ./hsh
/home/edwin/.vscode-server/bin/dfd34e8260c70da74b5c2d86d61aee4b6d56977/bin/remote-cli:/usr/local/sbin:/usr/local/bin...
~~~

### Command Excution :printer:

After receiving a command, **hsh** tokenizes it into words using ** " "**  as a delimiter. The first word is considered the command and all remaining words are considered arguments to that command. **hsh** then proceeds with the following actions:

* If the first character of the command is neither a slash (\) nor dot (.), the shell searches for it in the list of shell builtins. If there exists a builtin by that name, the builtin is invoked.
* If the first character of the command is none of a slash (\), dot (.), nor builtin, **hsh** searches each element of the **PATH** environmental variable for a directory containing an executable file by that name.
* If the first character of the command is a slash (\) or dot (.) or either of the above searches was successful, the shell executes the named program with any remaining given arguments in a separate execution environment.

### Variable Replacement :pushpin:

**hsh** interprets the $ character for variable replacement.

### $ENV_VARIABLE

**ENV_VARIABLE** is substituted with its value.

Example:

~~~
$ echo "echo $PWD" | ./hsh 
/home/edwin/simple_shell
~~~

### $?

**?** is substitued with the return value of the last program executed.

Example:

~~~
$ echo "echo $?" | ./hsh
0
~~~

### $$

In this case the second $ is substitued with the current process ID.

Example:

~~~
$ echo "echo $$" | ./hsh

~~~




### Authors :crayon:

* Edwin Gavíria

* Yoshua López

*Alejandro Aragón
