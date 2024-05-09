#include "minishell.h"

void	execution_cases(t_shell *shell_info, int *status)
{
	pid_t		pid;
	
		if (num_of_total_cmds(shell_info->first_command) == 1) // create pipes before redirections, if I have a redir I should over-write the pipe(fd) with the file fd
			pid = exec_single_cmd(shell_info, shell_info->first_command);
		else
			pid = exec_pipeline(shell_info);
		waitpid(pid, status, 0);
		*status = handle_exit(*status);
	write(2, "EXITING execution_cases\n", ft_strlen("EXITING execution_cases\n"));
}

pid_t	exec_pipeline(t_shell *shell_info)
{
	t_command	*iterate_cmd;
	pid_t		pid;

	iterate_cmd = shell_info->first_command;
	while (iterate_cmd)
	{
		write(2, "ENTERED ITER LOOP\n", ft_strlen("ENTERED ITER LOOP\n"));
		if (pipe(shell_info->fd) == -1)
			perror("pipe failed");
		// if (iterate_cmd != get_last_cmd(shell_info->first_command))
			// init_pipe(shell_info, iterate_cmd);
		dup2(shell_info->fd[1], STDOUT_FILENO);
		close(shell_info->fd[1]);
		// sleep(6);
		pid = exec_single_cmd(shell_info, iterate_cmd);
		dup2(shell_info->fd[0], STDIN_FILENO);
		close(shell_info->fd[0]);
		iterate_cmd = iterate_cmd->next;
	}
	write(2, "EXITING ITER LOOP\n", ft_strlen("EXITING ITER LOOP\n"));
	return (pid);
}

pid_t	exec_single_cmd(t_shell *shell_info, t_command	*cmd_to_exec)
{
	pid_t		pid;
	// t_command	*cmd_to_exec;
	char		*full_path;  // ADD TO STRUCT!

	pid = fork();
	if (pid == 0)
	{
		// if (num_of_total_cmds(shell_info->first_command) > 1) // create pipes before redirections, if I have a redir I should over-write the pipe(fd) with the file fd
		// 	init_pipe(shell_info, cmd_to_exec);
		handle_redir(shell_info, cmd_to_exec);
		full_path = find_cmd_in_env(cmd_to_exec->cmd, shell_info->env);
		if (!full_path)
			exit (127);
		// print_split(cmd_to_exec->full_cmd);
		execve(full_path, cmd_to_exec->full_cmd, shell_info->env);
		printf("passed execve\n");
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		// printf("WAITPID\n");
		// close_fds(shell_info, cmd_to_exec);
		// waitpid(pid, status, 0);
		return (pid);
	}
}

void	init_pipe(t_shell *shell_info, t_command *cur) //delete function?
{
	t_command	*last_cmd;
	t_command	*first_cmd;

	first_cmd = shell_info->first_command;
	last_cmd = get_last_cmd(first_cmd);
	if (cur == first_cmd)
	{
		close(shell_info->fd[0]);
		dup2(shell_info->fd[1], STDOUT_FILENO); //add checks for dup2?
	}
	else if (cur == last_cmd)
	{
		close(shell_info->fd[1]);
		dup2(shell_info->fd[0], STDIN_FILENO);
	}
	else // i need both ends of the pipe if my command is in between pipes else I have separate for first and last commands
	{
		dup2(shell_info->fd[0], STDIN_FILENO);
		dup2(shell_info->fd[1], STDOUT_FILENO);
	}
}

void	handle_redir(t_shell *shell_info, t_command *cur) ///////close pipe in each case
{
	if (cur->input_fd != -1)
	{
		if (shell_info->fd[0] != -1)
			close(shell_info->fd[0]); //do it even if file fails ot not?
		if (dup2(cur->input_fd, STDIN_FILENO) == -1) //cur->standard_input from initialise_cmd_node
		{
			perror("dup2 for input_fd failed");
			exit(EXIT_FAILURE);
		}
		close(cur->input_fd);
	}
	if (cur->output_fd != -1)
	{
		if (shell_info->fd[1] != -1)
			close(shell_info->fd[1]);
		if (dup2(cur->output_fd, STDOUT_FILENO) == -1) //cur->standard_output from initialise_cmd_node
		{
			perror("dup2 for output_fd failed");
			exit(EXIT_FAILURE);
		}
		close(cur->output_fd);
	}
}
