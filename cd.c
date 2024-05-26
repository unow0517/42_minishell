/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:03:00 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/30 19:00:38 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_mini	*env_search_name(char *name, t_env_mini *env_mini)
{
	if (!name || !env_mini)
		return (0);
	while (env_mini)
	{
		if (inputis(env_mini->name, name))
			return (env_mini);
		if (env_mini->next)
			env_mini = env_mini->next;
		else
			break ;
	}
	return (0);
}

void	run_cd(char *inpt, t_shell *shell_info)
{
	char		*path_input;
	char		cwd[1024];
	t_env_mini	*env_mini;
	t_env_mini	*env_mini_pwd;
	t_env_mini	*env_mini_oldpwd;

  	getcwd(cwd, sizeof(cwd));
  	env_mini_pwd = 0;
  	env_mini_oldpwd = 0;
  	env_mini_pwd = env_search_name("PWD", shell_info->env_mini);
  	env_mini_oldpwd = env_search_name("OLDPWD", shell_info->env_mini);
  	path_input = inpt;
	if (chdir(path_input) == -1)
	{
		*(shell_info->status) = 1;
	  	ft_printf("minishell: cd : %s: No such file or directory\n", path_input);	
	}
	else
	{
		getcwd(cwd, sizeof(cwd));
		ft_memset(shell_info->oldpwd, 0, 1024);
		ft_strlcat(shell_info->oldpwd, shell_info->cwd, 1024);
		ft_memset(shell_info->cwd, 0, 1024);
		ft_strlcat(shell_info->cwd, cwd, 1024);
	  	env_mini_pwd->value = shell_info->cwd;
	  	if (env_mini_oldpwd)
	    	env_mini_oldpwd->value = shell_info->oldpwd;
	  	else
	  	{
	    	env_mini = ft_lstnew_envmini("OLDPWD", shell_info->oldpwd);
	    	ft_lstlast_envmini(shell_info->env_mini)->next = env_mini;
	  	}
		*(shell_info->status) = 0;
	}
}