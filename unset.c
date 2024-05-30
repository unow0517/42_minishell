/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:51:49 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/30 21:10:13 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_path_in_envmini(t_env_mini *env_mini)
{
	char	**output;

	output = NULL;
	while (env_mini)
	{
		if (inputis(env_mini->name, "PATH"))
		{
			output = ft_split(env_mini->value, ':');
			return (output);
		}
		if (env_mini->next)
			env_mini = env_mini->next;
		else
			break ;
	}
	return (output);
}

void	rm_in_lnli(char *str, t_env_mini *lnli)
{
	t_env_mini	*prev;

	while (lnli)
	{
		if (inputis(lnli->name, str))
		{
			prev->next = lnli->next;
			free_env_node(lnli);
			break ;
		}
		prev = lnli;
		if (lnli->next)
			lnli = lnli->next;
		else
			break ;
	}
}

void	free_env_node(t_env_mini *lnli)
{
	if (lnli->name)
	{
		free(lnli->name);
		lnli->name = NULL;
	}
	if (lnli->value)
	{
		free(lnli->value);
		lnli->value = NULL;
	}
	free(lnli);
	lnli = NULL;
}

void	run_unset(char *str, t_shell *shell_info)
{
	char	**var_names;
	int		i;

	i = 0;
	if (!str || inputis(str, ""))
		rl_on_new_line();
	else
	{
		var_names = ft_split(str, ' ');
		while (var_names[i])
		{
			rm_in_lnli(var_names[i], shell_info->env_mini);
			i++;
		}
		if (var_names)
		{
			free_split_thalia(var_names);
			var_names = NULL;
		}
	}
	proc_exit(0, shell_info);
}
