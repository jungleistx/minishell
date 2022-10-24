# minishell

## About
Minishell is the second project of the Unix-branch in Hive Helsinki. <br>

This is my implementation of a simple command-line interpreter.

## Allowed functions
* malloc, free
* access
* open, close, read, write
* opendir, readdir, closedir
* getcwd, chdir
* stat, lstat, fstat
* fork, execve
* wait, waitpid, wait3, wait4
* signal, kill
* exit

## Usage

1. make
2. ./minishell

## Builtin commands & functionality
* echo
* cd
* setenv
* unsetenv
* env
* exit
* expansions of '$' and '~'

## Example usage
``` 
./minishell
ls -l
-rw-r--r--  1 owner  group     9 28 Sep 12:30 author
-rw-r--r--  1 owner  group  4468 28 Sep 12:30 ft_ls.h
exit
```

## Features not supported 
* Open quotes
* Redirections
* Pipes
* Multiple commands separated by ';'
