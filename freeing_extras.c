/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_extras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:14:13 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/31 13:05:00 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split_set_null(char **keywords)
{
	if (keywords)
	{
		free_split_thalia(keywords);
		keywords = NULL;
	}
}

void	free_set_null(char *str)
{
	if (str)
	{
		free(str);
		str = NULL;
	}
}

void	free_envmini(t_env_mini *env_mini)
{
	t_env_mini	*next_node;
	t_env_mini	*current;

	current = env_mini;
	next_node = current;
	while (next_node != NULL)
	{
		if (current)
			next_node = current->next;
		if (current->name && ft_strlen(current->name) > 0)
			free(current->name);
		if (current->value && ft_strlen(current->value) > 0)
			free(current->value);
		if (current)
		{
			free(current);
			current = NULL;
		}
		current = next_node;
	}
	env_mini = NULL;
}
