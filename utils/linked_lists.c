/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:32:39 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 11:37:24 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	token_count(t_shell *shell_info)
{
	int		counter;
	t_token	*iter;

	iter = shell_info->tokens;
	counter = 0;
	while (iter)
	{
		iter = iter->next;
		counter++;
	}
	return (counter);
}
