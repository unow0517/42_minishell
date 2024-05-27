/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:51:49 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/13 14:42:28 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_env(t_shell *shell_info)
{
	t_env_mini	*env_mini;

	env_mini = shell_info->env_mini;
	while (env_mini)
	{
		if (env_mini->value)
			printf("%s=%s\n", env_mini->name, env_mini->value);
		env_mini = env_mini->next;
	}
	*(shell_info->status) = 0;
}