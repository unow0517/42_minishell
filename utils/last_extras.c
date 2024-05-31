/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_extras.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:52:57 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/31 11:23:08 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*repl_exp_return(char *str_till_dollar, char *str_after_varname)
{
	char	*return_str;

	return_str = ft_strjoin(str_till_dollar, str_after_varname);
	free_set_null(str_till_dollar);
	return (return_str);
}

t_env_mini	*env_to_envmini_helper(t_env_mini *env_mini)
{
	env_mini->next = ft_calloc(1, sizeof(t_env_mini));
	if (env_mini->next)
		env_mini = env_mini->next;
	return (env_mini);
}

void	run_export_keyword_error(int *status, char *var_name, \
char *var_value, char *ptr)
{
	(*status)++;
	printf("minishell: export: `%s' not a valid identifier\n", ptr);
	if (var_name)
		free_set_null(var_name);
	if (var_value)
		free_set_null(var_value);
	if (ptr)
		free_set_null(ptr);
}

void	cd_helper(t_shell *shell_info, char *cwd)
{
	getcwd(cwd, sizeof(cwd));
	update_pwd(cwd, shell_info);
	proc_exit(0, shell_info);
}
