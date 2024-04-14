# 42_minishell

## Must Know
### Key Points in the project Pipex, of which I did Minitalk instead.
* **Prompt** : refers to a message or text displayed to the user to solicit input or provide instructions.
* **Pipe** : Pipe is one-way communication only i.e we can use a pipe such that One process write to the pipe, and the other process reads from the pipe.
* **File Descriptor** : File descriptor refers to a numeric number identifier used in operating systems, meaning it's a special number that a computer uses to track files and devices it is using.

```c
int pipe(int fds[2])
Parameters :
fd[0] will be the fd(file descriptor) for the 
read end of pipe.
fd[1] will be the fd for the write end of pipe.
```

* **Fork** : to create a new system(*child process*), which runs concurrently with the process called fork function(*parent process*). Both processes execute following instructions.

*Return*:<br/>
Negative: The creation of a child process was unsuccessful.<br/>
Zero: Returned to the newly created child process.<br/>
Positive: Returned to parent or caller. The value contains the process ID of the newly created child process.<br/>

* **third parameter in main for environment variables** : env variables can be accessed with the third variable in main function. [More info](https://stackoverflow.com/questions/10321435/is-char-envp-as-a-third-argument-to-main-portable)
```c
void	child1_process(int *fd, char **argv, char **env)
{
  //my code
}
```
* **`int dup2(int oldfd, int newfd);`** : duplicates value of oldfd to new fd.

