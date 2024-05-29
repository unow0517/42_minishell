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

void	update_pwd(char *str, t_shell *shell_info)
{
	// char		cwd[2048];
	t_env_mini	*env_mini;
	t_env_mini	*env_mini_pwd;
	t_env_mini	*env_mini_oldpwd;

	// getcwd(cwd, sizeof(cwd));
	env_mini_pwd = env_search_name("PWD", shell_info->env_mini);
	env_mini_oldpwd = env_search_name("OLDPWD", shell_info->env_mini);
	ft_memset(shell_info->oldpwd, 0, 2048);
	ft_strlcat(shell_info->oldpwd, shell_info->cwd, 2048);
	ft_memset(shell_info->cwd, 0, 2048);
	ft_strlcat(shell_info->cwd, str, 2048);
	env_mini_pwd->value = shell_info->cwd;
	if (env_mini_oldpwd)
		env_mini_oldpwd->value = shell_info->oldpwd;
	else
	{
		env_mini = ft_lstnew_envmini("OLDPWD", shell_info->oldpwd);
		ft_lstlast_envmini(shell_info->env_mini)->next = env_mini;
	}
}

char	*rm_outest_quote_cd(char *str, t_shell *shell_info)
{
	char	q;
	char	*str_q_removed;
	char	**splitted;

	if (ft_strchr(str, '\'') != 0 || ft_strchr(str, '"') != 0)
	{
		q = first_quote(str);
		str_q_removed = rm_quotes(str, q);
		return (str_q_removed);
	}
	else
	{
		splitted = ft_split(str, ' ');
		if (splitted[1])
		{
			*(shell_info->status) = 1;
			printf("minishell: cd : too many arguments\n");
			return (0);
		}
		return (str);
	}
}

void	run_cd(char *inpt, t_shell *shell_info)
{
	char		*path_input;
	char		cwd[2048];
	t_env_mini	*env_mini_home;
	// int			status;

	// status = 0;
	if (!inpt || !*inpt)
		return ;
	path_input = rm_outest_quote_cd(inpt, shell_info);
	if (!path_input)
		return ;
	getcwd(cwd, sizeof(cwd));
	env_mini_home = env_search_name("HOME", shell_info->env_mini);
	if (inputis(inpt, "~"))
	{
		// status = 1;
		update_pwd(env_mini_home->value, shell_info);
		proc_exit(0, shell_info);
	}
	else if (chdir(path_input) == -1)
	{
		proc_exit(1, shell_info);
		printf("minishell: cd : %s: No such file or directory\n",
			path_input);
	}
	else
	{
		getcwd(cwd, sizeof(cwd));
		update_pwd(cwd, shell_info);
		proc_exit(0, shell_info);
	}
}
