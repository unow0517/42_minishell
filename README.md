# 42_minishell
 To make my own shell.<br/>
 **Knowledge from previous Project Minitalk and PipeX is required.** 
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

* **third parameter in main for environment variables** : env variables can be accessed with the third variable in main function. [More](https://stackoverflow.com/questions/10321435/is-char-envp-as-a-third-argument-to-main-portable)
```c
void	child1_process(int *fd, char **argv, char **env)
{
  //my code
}
```
* **`int dup2(int oldfd, int newfd);`** : duplicates value of oldfd to new fd.
* **`int access( const char * path,int amode );`** : checks to see if the file or directory specified by path exists and if it can be accessed with the file access permissions given by amode. [More](https://www.qnx.com/developers/docs/7.1/#com.qnx.doc.neutrino.lib_ref/topic/a/access.html)
* **`int execve(const char *pathname, char *const _Nullable argv[], char *const _Nullable envp[]);`**: execve() executes the program referred to by pathname.  This causes the program that is currently being run by the calling process to be replaced with a new program, with newly initialized stack, heap, and (initialized and uninitialized) data segments.[More](https://man7.org/linux/man-pages/man2/execve.2.html)
* **`pid_t waitpid(pid_t pid, int *status_ptr, int options);`** : Suspends the calling process until a child process ends or is stopped. status = Points to a location where waitpid() can store a status value. [More](https://www.ibm.com/docs/en/zvm/7.3?topic=descriptions-waitpid-wait-specific-child-process-end)

### Parsing

* **Canonical** :
  In canonical input processing mode, **terminal input is processed in lines terminated by newline ('\n'), EOF(EndOfFile), or EOL(EndOfLine) characters**. No input can be read until an entire line has been typed by the user, and the read function (see I/O Primitives) returns at most a single line of input, no matter how many bytes are requested.
* **Noncanonical** : In noncanonical input processing mode, **characters are not grouped into lines, and ERASE and KILL processing is not performed**. The granularity with which bytes are read in noncanonical input mode is controlled by the MIN and TIME settings.
* **STDIN_FILENO** : is **a predefined constant representing the file descriptor** associated with the standard input stream, typically the keyboard. It's defined in the <unistd.h> header file. When you run a program from the command line and type something into it, you're providing input via stdin.
<br/><br/>
## To read
https://techdebt.tistory.com/33
