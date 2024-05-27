/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:51:49 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/27 10:57:57 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_path_in_envmini(t_env_mini *env_mini)
{
	char	**output;

	output = 0;
	while (env_mini)
	{
			// printf("HOO\n");
		if (inputis(env_mini->name, "PATH"))
		{

			// printf("hello\n");
			output = ft_split(env_mini->value, ':');
			// printf("op 0 %s\n", output[0]);
			return (output);
		}
	// printf("helloaaa\n");
		
		if (env_mini->next)
			env_mini = env_mini->next;
		else
			break ;
	}
	// printf("hellobbbb\n");
	// printf("op %d\n", output == 0);
	// if (!output)
	// {
	// 	*(shell_info->status) = 1;
	// 	ft_printf("minishell: %s: No such file or directory\n", path_input);	
	// }
	return (output);
}

void	rm_in_lnli(char *str, t_env_mini *lnli)
{
	t_env_mini *prev;

	while (lnli)
	{
    	if (inputis(lnli->name, str))
		{
    		prev->next = lnli->next;
    		free(lnli);
    		break ;
    	}
    	prev = lnli;
    	if (lnli->next)
    		lnli=lnli->next;
		else
			break ;
	}
}

void	run_unset(char *str, t_shell *shell_info)
{
	char		*inpt;
	// t_env_mini	*env_mini;
	char		**var_names;
	int			i;

	inpt = str;
	i = 0;
	// //OPTION 1. WHEN THE WHOLE INPUT IS PASSED.
	// if (inputis(inpt, "unset"))
	// 	rl_on_new_line();
	// else if (inputstartswith(inpt, "unset "))
	// {
	// OPTION 1 END
	
	//OPTION 2. WHEN THE WHOLE INPUT IS PASSED.
	if (!inpt || inputis(inpt, ""))
		rl_on_new_line();
	else
	{
	//OPTION 2 END

		var_names = ft_split(inpt, ' ');
		while (var_names[i])
		{
			rm_in_lnli(var_names[i], shell_info->env_mini);
			i++;
		}
	}
	*(shell_info->status) = 0;
}

//ft_split free required!
