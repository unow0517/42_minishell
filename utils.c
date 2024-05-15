/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:08:36 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/15 16:37:29 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_add_back(t_command **first_token, t_command *new)
{
	t_command	*end;

	if (!first_token || !new)
		return ;
	if (!*first_token)
	{
		*first_token = new;
		return ;
	}
	end = get_last_cmd(*first_token);
	end->next = new;
}

t_command	*get_last_cmd(t_command *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	token_add_back(t_token **first_token, t_token *new)
{
	t_token	*end;

	if (!first_token || !new)
		return ;
	if (!*first_token)
	{
		*first_token = new;
		return ;
	}
	end = token_last(*first_token);
	end->next = new;
}

t_token	*token_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token && token->next)
		token = token->next;
	return (token);
}


int	skip_whitespace(char *inpt, int i)
{
	while (inpt[i] != '\0' && (inpt[i] == ' ' || inpt[i] == '\t' || inpt[i] == '\r' ||\
	 inpt[i] == '\n' || inpt[i] == '\v' || inpt[i] == '\f'))
	 	i++;
	return (i);
}

bool	is_metacharacter(char c)
{
	if (c == '|' || c =='>' || c == '<' || c == '"' || c == '\'')
		return (true);
	return (false);
}

bool	is_metacharacter_type(int i)
{
	if (i == PIPE || i == S_QUOTE || i == D_QUOTE || i == S_LESS ||\
	 i == S_MORE || i == D_LESS || i == D_MORE)
		return (true);
	return (false);
}

bool	is_redir(int i)
{
	if (i == S_LESS || i == S_MORE || i == D_LESS || i == D_MORE)
		return (true);
	return (false);
}

bool	is_ws(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

int	num_of_remaining_cmds(t_command *cur) //check if needed
{
	int	counter;

	counter = 0;
	while (cur)
	{
		cur = cur->next;
		counter++;
	}
	return (counter);
}

int	num_of_total_cmds(t_command *cur)
{
	int	counter;

	counter = 0;
	while (cur)
	{
		cur = cur->next;
		counter++;
	}
	return (counter);
}

void	close_fds(t_shell *shell_info, t_command *cur)
{
	if (cur->input_fd != -1)
		close(cur->input_fd);
	if (cur->output_fd != -1)
		close(cur->output_fd);
	if (shell_info->fd[0] != -1)
		close(shell_info->fd[0]);
	if (shell_info->fd[1] != -1)
		close(shell_info->fd[1]);
}

int	handle_exit(int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = EXIT_FAILURE;
	return (status);
}

int	token_count(t_shell *shell_info)
{
	int	counter;
	t_token *iter;

	iter = shell_info->tokens;
	counter = 0;
	while (iter)
	{
		iter = iter->next;
		counter++;
	}
	return (counter);
}
