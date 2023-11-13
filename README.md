# Pipex

Pipex is my first little unix project. It is a base for a bigger later project (minishell) of the 42 Curriculum at Hive Helsinki.
It aims to imitate the behaviour of a pipe by a limited use of functions such as:
open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid.

In this project I learned the first time about processes, how to fork to get multiple processes and how the order and waiting of processes matter.
It was the first project using a struct for me and learning how to learn and implement new information and coding techniques. 

## Example

The execution is done as following:

./pipex file1 cmd1 cmd2 file2

Which is supposed to work as:

< file1 cmd1 | cmd2 > file2
