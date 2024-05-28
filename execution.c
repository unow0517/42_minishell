/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:12:00 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/25 18:12:00 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//YUN: RUN CMD OR PIPE DEPENDING ON THE # OF CMDS
void	execution_cases(t_shell *shell_info)
{
	pid_t	pid;

	pid = 0;
	if (shell_info->syntax_error == false)
	{
		if (num_of_total_cmds(shell_info->first_command) == 1 && \
		shell_info->first_command->is_builtin == true)
			execute_builtin(shell_info, shell_info->first_command);
		// else if (num_of_total_cmds(shell_info->first_command) == 1)
		// 	pid = exec_single_cmd(shell_info, shell_info->first_command);
		else
			pid = exec_pipeline(shell_info);
		waitpid(pid, shell_info->status, 0);
		while (waitpid(-1, NULL, WNOHANG) != -1) //WUNTRACED
			;
		// while (waitpid(pid, shell_info->status, WNOHANG) != -1) //WUNTRACED
		// 	;
		*shell_info->status = handle_exit(*shell_info->status);
	}
}

void execute_builtin(t_shell *shell_info, t_command *cmd)
{
	if (inputis(cmd->builtin_type, "echo"))
		run_echo(cmd->builtin_arg, shell_info);
	else if (inputis(cmd->builtin_type, "cd"))
		run_cd(cmd->builtin_arg, shell_info);
	else if (inputis(cmd->builtin_type, "pwd"))
		run_pwd(shell_info);
	else if (inputis(cmd->builtin_type, "env"))
		run_env(shell_info);
	else if (inputis(cmd->builtin_type, "export"))
		run_export(cmd->builtin_arg, shell_info);
	else if (inputis(cmd->builtin_type, "unset"))
		run_unset(cmd->builtin_arg, shell_info);
	else if (inputis(cmd->builtin_type, "history"))
		print_history(shell_info);
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
	close_pipes(shell_info);
	return (pid);
}

pid_t	exec_single_cmd(t_shell *shell_info, t_command *cmd_to_exec)
{
	pid_t		pid;
	char		*full_path;
	char		**paths_in_env;

	paths_in_env = ft_path_in_envmini(shell_info->env_mini);
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
		if (cmd_to_exec->file_not_found == 0)
		{
			if (cmd_to_exec->is_builtin == true)
				execute_builtin(shell_info, cmd_to_exec);
			else
			{
				if (cmd_to_exec->cmd == NULL)
					exit(0); ///check exit value
				// if (cmd_to_exec->cmd[0] == '\0')
				// 	exit(0); 
				full_path = find_cmd_in_env_mini(cmd_to_exec->cmd, paths_in_env);
				if (!full_path || !paths_in_env)
					cmd_error(cmd_to_exec); // exit (127);
				execve(full_path, cmd_to_exec->full_cmd, paths_in_env);
				free(full_path);
				cmd_error(cmd_to_exec);
			}
		}
		close_fds(shell_info, cmd_to_exec);
		exit(EXIT_FAILURE);
	}
	else //YUN: CODE IS RUNNING ON PARENT PROCESS, RETEURNS CHILD PROCESS
	{
		close_fds(shell_info, cmd_to_exec);
		return (pid);
	}
}

//CONNECT STDIN TO CURRENT CMD, STDOUT TO NEXT CMD, HANDLING FILE DESCRIPTOR
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

void	close_pipes(t_shell *shell_info)
{
	t_command	*iterate;

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
			close(shell_info->fd[0]);
		if (dup2(cur->input_fd, STDIN_FILENO) == -1)
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
		if (dup2(cur->output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 for output_fd failed");
			exit(EXIT_FAILURE);
		}
		close(cur->output_fd);
	}
}

//DIFFERENCE BETWEEN CMD FD[2] AND SHELL FD[2]?