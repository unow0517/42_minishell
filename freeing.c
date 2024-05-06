/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:13:23 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/06 13:35:37 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*del;
	t_token	*temp;

	del = *tokens;
	while (del)
	{
		temp = del;
		del = del->next;
		free(temp);
	}
	*tokens = NULL;
}

void	free_cmd_list(t_command **cmds)
{
	t_command	*del;
	t_command	*temp;

	del = *cmds;
	while (del)
	{
		temp = del;
		del = del->next;
		if (temp->cmd)
			free(temp->cmd);
		if (temp->full_cmd)
			free(temp->full_cmd);
		if (temp->options)
			free(temp->options);
		if (temp->input_fd >= 0)
			close(temp->input_fd);
		if (temp->output_fd >= 0)
			close(temp->output_fd);
		free(temp);
	}
	*cmds = NULL;
}
