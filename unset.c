/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:51:49 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/10 11:14:09 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_in_lnli(char *str, t_env_mini *lnli)
{
	if (ft_strncmp(lnli->name, str, ft_strlen(str)) == 0)
	{
		free(lnli);
		lnli = lnli->next;
	}
	while (lnli)
	{
		if (ft_strncmp(lnli->name, str, ft_strlen(str)) == 0)
		{
			
		}
		lnli=lnli->next;
	}
}
void	run_unset(t_shell *shell_info)
{
	char		*inpt;
	// t_env_mini	*env_mini;
	char		**var_names;
	int			i;

	inpt = shell_info->user_input;
	i = 1;
	if (inputis(inpt, "unset"))
		rl_on_new_line();
	else if (inputstartswith(inpt, "unset "))
	{
		var_names = ft_split(inpt, ' ');
		while (var_names[i])
		{
			rm_in_lnli(var_names[i], shell_info->env_mini);
			i++;
		}
	}
}
