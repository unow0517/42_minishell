/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:09:53 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/29 16:09:00 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_declare_env(t_shell *shell_info)
{
	t_env_mini	*env_mini;

	env_mini = shell_info->env_mini;
	while (env_mini)
	{
		if (env_mini->value)
			printf("declare -x %s=\"%s\"\n", env_mini->name, env_mini->value);
		else
			printf("declare -x %s\n", env_mini->name);
		if (env_mini->next)
			env_mini = env_mini->next;
		else
			break ;
	}
	proc_exit(0, shell_info);
}

t_env_mini	*ft_lstnew_envmini(char *name, char *value)
{
	t_env_mini	*first_node;

	first_node = (t_env_mini *)malloc(sizeof(t_env_mini));
	first_node->name = name;
	first_node->value = value;
	first_node->next = 0;
	return (first_node);
}

t_env_mini	*ft_lstlast_envmini(t_env_mini *lst)
{
	t_env_mini	*result;

	if (!lst)
		return (0);
	result = lst;
	while (result->next != 0)
		result = result->next;
	return (result);
}

int	is_al_num_underscore(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str && str)
	{
		if (ft_isalnum(*str) || *str == '_')
			str++;
		else
			return (0);
	}
	return (1);
}
