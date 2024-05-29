/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 17:51:49 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/13 15:16:58 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*export_rm_quote(char *str)
{
	char	*output;
	char	q;
	char	*str_q_removed;

	if (ft_strchr(str, '\'') != 0 || ft_strchr(str, '"') != 0)
	{
		q = first_quote(str);
		str_q_removed = rm_quotes(str, q);
		output = str_q_removed;
	}
	else
		output = str;
	return (output);
}

char	*find_varname(char *str)
{
	char	*ptr_to_equal;
	char	*var_name;

	ptr_to_equal = ft_strchr(str, '=');
	if (ptr_to_equal == 0)
		var_name = str;
	else
		var_name = ft_substr(str, 0, ptr_to_equal - str);
	return (var_name);
}

char	*find_varvalue(char *str)
{
	char	*ptr_to_equal;
	char	*var_value;

	ptr_to_equal = ft_strchr(str, '=');
	if (ptr_to_equal == 0)
		var_value = NULL;
	else
		var_value = ft_substr(ptr_to_equal + 1, 0, ft_strlen(ptr_to_equal));
	return (var_value);
}

void	run_export_keyword(char	*str, t_shell *shell_info)
{
	char		*var_name;
	char		*var_value;
	t_env_mini	*env_mini;
	char		*ptr;

	ptr = export_rm_quote(str);
	var_name = find_varname(ptr);
	var_value = find_varvalue(ptr);
	if (!var_name || !is_al_num_underscore(var_name))
	{
		proc_exit(1, shell_info);
		printf("minishell: export: `%s' not a valid identifier\n", str);
	}
	else if (is_al_num_underscore(var_name))
	{
		env_mini = ft_lstnew_envmini(var_name, var_value);
		ft_lstlast_envmini(shell_info->env_mini)->next = env_mini;
		proc_exit(0, shell_info);
	}
}

void	run_export(char *str, t_shell *shell_info)
{
	char	*inpt;
	char	**keywords;

	inpt = str;
	if (!str || !ft_strlen(inpt))
		run_declare_env(shell_info);
	else
	{
		keywords = ft_split(inpt, ' ');
		while (keywords && *keywords)
		{
			run_export_keyword(*keywords, shell_info);
			keywords++;
		}
	}
}
