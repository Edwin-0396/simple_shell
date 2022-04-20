# **Simple_Shell** :shell:

## Description :scroll:

In this project we are tasked with creating our own simple UNIX command interpreter. The program must have the exact same output as sh (/bin/sh) as well as the exact same error output.

### Invocation

Usage: **hsh**[filename]

To invocate **hsh**, compile all **.c** files in the repository and run the resulting executable:

~~~
gcc *.c -o hsh
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
