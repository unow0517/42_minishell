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
		free_temp(temp);
	}
	*cmds = NULL;
}

void	free_temp(t_command *temp)
{
	if (temp->cmd)
		free(temp->cmd);
	if (temp->options)
		free_split_thalia(temp->options);
	if (temp->full_cmd)
		free_split_thalia(temp->full_cmd);
	close_io(temp);
	if (temp->filename)
		free(temp->filename);
	if (temp->builtin_type)
		free(temp->builtin_type);
	if (temp->builtin_arg)
		free(temp->builtin_arg);
	if (temp->to_split && temp->to_split[0] != '\0')
		free(temp->to_split);
	free(temp);
}

void	free_shell(t_shell *shell_info)
{
	free(shell_info->user_input);
	free(shell_info->status);
}

void	free_split_thalia(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = 0;
}
