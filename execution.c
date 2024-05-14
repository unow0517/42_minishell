#include "minishell.h"

//YUN: RUN CMD OR PIPE DEPENDING ON THE # OF CMDS
void	execution_cases(t_shell *shell_info, int *status)
{
	pid_t		pid;
	
	//builtins
	if (num_of_total_cmds(shell_info->first_command) == 1)
		// pid = exec_single_cmd(shell_info, shell_info->first_command);
    //YUN: execution.c:6:25: error: variable ‘pid’ set but not used [-Werror=unused-but-set-variable]
		pid = exec_single_cmd(shell_info, shell_info->first_command);
	else
		pid = exec_pipeline(shell_info);
	//YUN: -1 : WAITING FOR ANY CHILD PROC. IF CHILD PROCESS IS SUCCESSFULLY MADE THEN ?
	//YUN: WNOHANG return immediately if no child has exited.
	//YUN: ; = DOING NOTHING?
  //YUN: some builtin fns do not need child process.
	while (waitpid(-1, NULL, WNOHANG) != -1) //WUNTRACED 
		;
  ft_printf("pid execution.c %d", pid); // YUN : TO AVOID ERR IN LINUX
  *status = handle_exit(*status);
}

//YUN: ITERATE TO RUN COMMANDS, shell_info->first_command IS LINKED LIST OF CMD STRUCTS
pid_t	exec_pipeline(t_shell *shell_info)
{
	t_command	*iterate_cmd;
	pid_t		pid;

	iterate_cmd = shell_info->first_command;
	while (iterate_cmd)
	{
		pid = exec_single_cmd(shell_info, iterate_cmd);
		iterate_cmd = iterate_cmd->next;
	}
	//YUN: CLOSE FILE DESCRIPTOR[0], [1] OF LINKED LIST OF CMD STRUCTS
	close_pipes(shell_info);
	return (pid);
}

pid_t	exec_single_cmd(t_shell *shell_info, t_command	*cmd_to_exec)
{
	pid_t		pid;
	char		*full_path;  // ADD TO STRUCT!

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		pipe_handling(shell_info, cmd_to_exec);
		handle_redir(shell_info, cmd_to_exec);
		full_path = find_cmd_in_env(cmd_to_exec->cmd, shell_info->env);
		if (!full_path)
			exit (127);
// sleep(999999999);
		execve(full_path, cmd_to_exec->full_cmd, shell_info->env);
		// printf("passed execve\n");
		perror("execve");
		close_fds(shell_info, cmd_to_exec);
		exit(EXIT_FAILURE);
	}
	else
	{
		close_fds(shell_info, cmd_to_exec);
		return (pid);
	}
}

void	pipe_handling(t_shell *shell_info, t_command *cur)
{
	t_command	*last_cmd;
	t_command	*first_cmd;

	first_cmd = shell_info->first_command;
	last_cmd = get_last_cmd(first_cmd);
	if (cur != last_cmd)
		dup2(cur->next->fd[1], STDOUT_FILENO);
	if (cur != first_cmd)
		dup2(cur->fd[0], STDIN_FILENO);
	close_pipes(shell_info);
}

void close_pipes(t_shell *shell_info)
{
	t_command *iterate;

	iterate = shell_info->first_command;
	while (iterate)
	{
		close(iterate->fd[0]);
		close(iterate->fd[1]);
		iterate = iterate->next;
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
