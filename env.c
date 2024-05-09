/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:51:49 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/09 15:40:34 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_env(t_shell *shell_info)
{
	// char	**env;

	// env = shell_info->env;
	// while (env && *env)
	// {
	// 	printf("%s\n",*env);
	// 	env++;
	// }	

	t_env_mini *env_mini;

	env_mini = shell_info->env_mini;
	while (env_mini)
	{
		if (env_mini->value)
			ft_printf("%s=%s\n", env_mini->name, env_mini->value);
		env_mini = env_mini->next;
	}
}