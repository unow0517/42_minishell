/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:33:19 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 12:40:05 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_fds(t_shell *shell_info, t_command *cur)
{
	close_io(cur);
	if (shell_info->fd[0] != -1)
		close(shell_info->fd[0]);
	if (shell_info->fd[1] != -1)
		close(shell_info->fd[1]);
}

void	close_io(t_command *cur)
{
	if (cur->input_fd != -1)
		close(cur->input_fd);
	if (cur->output_fd != -1)
		close(cur->output_fd);
}

int	handle_exit(int status)
{
	int	exit_code;
	int	signal;

	if (WIFEXITED(status) == 1)
		exit_code = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		exit_code = signal + 128;
	}
	return (exit_code);
}

void	reset(t_shell *shell_info)
{
	free_tokens(&shell_info->tokens);
	free_cmd_list(&shell_info->first_command);
	shell_info->syntax_error = false;
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
