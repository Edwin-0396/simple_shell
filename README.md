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

**hsh** can be onvoked both interactively an non-interactively. If **hsh** is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Example:

~~~
$ echo "echo 'hello'"| ./hsh
$
~~~
