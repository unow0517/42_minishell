#include "minishell.h"

void	executor(t_shell *shell_info, int *status, t_command *cur)
{
	pid_t		pid;
	char		*full_path;

	pid = fork();
	if (pid == 0)
	{
		if (num_of_total_cmds(shell_info->first_command) > 1) // create pipes before redirections, if I have a redir I should over-write the pipe(fd) with the file fd
			init_pipe(shell_info, cur);
		handle_redir(cur);
		full_path = find_cmd_in_env(cur->cmd, shell_info->env);
		// print_split(cur->full_cmd);
		execve(full_path, cur->full_cmd, shell_info->env);
		printf("passed execve\n");
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		close_fds(cur);
		waitpid(pid, status, 0);
	}
}

void	init_pipe(t_shell *shell_info, t_command *cur)
{
	t_command	*last_cmd;
	t_command	*first_cmd;

	first_cmd = shell_info->first_command;
	last_cmd = get_last_cmd(first_cmd);
	if (pipe(cur->fd) == -1)
	{
		perror("pipe failed"); //fix proper message and exit
		exit(1);
	}
	if (cur == first_cmd)
	{
		close(cur->fd[0]);
		dup2(cur->fd[1], STDOUT_FILENO); //add checks for dup2?
		// close(cur->fd[1]);
	}
	else if (cur == last_cmd)
	{
		close(cur->fd[1]);
		dup2(cur->fd[0], STDIN_FILENO);
		// close(cur->fd[0]);
	}
	else // i need both ends of the pipe if my command is in between pipes else I have separate for first and last commands
	{
		dup2(cur->fd[0], STDIN_FILENO);
		dup2(cur->fd[1], STDOUT_FILENO);
		// close(cur->fd[0]);
		// close(cur->fd[1]);
	}
}


void	handle_redir(t_command *cur)
{
	if (cur->input_fd != -1)
	{
		if (dup2(cur->input_fd, STDIN_FILENO) == -1) //cur->standard_input from initialise_cmd_node
		{
			perror("dup2 for input_fd failed");
			exit(EXIT_FAILURE);
		}
		close(cur->input_fd);
	}
	if (cur->output_fd != -1)
	{
		if (dup2(cur->output_fd, STDOUT_FILENO) == -1) //cur->standard_output from initialise_cmd_node
		{
			perror("dup2 for output_fd failed");
			exit(EXIT_FAILURE);
		}
		close(cur->output_fd);
	}
}

