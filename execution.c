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

void	execution_cases(t_shell *shell_info)
{
	pid_t	pid;

	pid = 0;
	if (shell_info->syntax_error == false)
	{
		if (num_of_total_cmds(shell_info->first_command) == 1 && \
		shell_info->first_command->is_builtin == true)
			execute_builtin(shell_info, shell_info->first_command);
		else
		{
			pid = exec_pipeline(shell_info);
			waitpid(pid, shell_info->status, 0);
			while (waitpid(-1, NULL, WNOHANG) != -1)
				;
			*shell_info->status = handle_exit(*shell_info->status);
		}
	}
}

void	execute_builtin(t_shell *shell_info, t_command *cmd)
{
	if (inputis(cmd->builtin_type, "echo"))
		run_echo(cmd->builtin_arg, shell_info, cmd->output_fd);
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

pid_t	exec_pipeline(t_shell *shell_info)
{
	t_command	*iterate_cmd;
	pid_t		pid;

	pid = 0;
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
	pid_t	pid;
	char	*full_path;
	char	**paths_in_env;

	pid = fork();
	if (pid == -1)
		fork_fail();
	if (cmd_to_exec->is_builtin == false)
	{
		paths_in_env = ft_path_in_envmini(shell_info->env_mini);
		full_path = find_cmd_in_env_mini(cmd_to_exec->cmd, paths_in_env);
	}
	if (pid == 0)
	{
		child_proccess(shell_info, cmd_to_exec, full_path, paths_in_env);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (cmd_to_exec->is_builtin == false)
			free_exec_paths(full_path, paths_in_env);
		close_fds(shell_info, cmd_to_exec);
		return (pid);
	}
}

void	child_proccess(t_shell *shell_info, t_command *cmd_to_exec, \
char *full_path, char **paths_in_env)
{
	pipe_handling(shell_info, cmd_to_exec);
	handle_redir(shell_info, cmd_to_exec);
	if (cmd_to_exec->file_not_found == 0)
		execute_cmd(shell_info, cmd_to_exec, full_path, paths_in_env);
	close_fds(shell_info, cmd_to_exec);
	if (cmd_to_exec->is_builtin == false)
		free_exec_paths(full_path, paths_in_env);
}
