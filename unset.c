/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:51:49 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/16 17:15:44 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_in_lnli(char *str, t_env_mini *lnli)
{
  t_env_mini *prev;

	while (lnli)
	{
    if (inputis(lnli->name, str))
	  {
      prev->next = lnli->next;
      free(lnli);
      break;
    }
    prev = lnli;
    if (lnli->next)
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

//ft_split free required!
