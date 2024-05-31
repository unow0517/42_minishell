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

	if (ft_strchr(str, '\'') != 0 || ft_strchr(str, '"') != 0)
	{
		q = first_quote(str);
		output = rm_quotes(str, q);
	}
	else
		output = ft_strdup(str);
	return (output);
}

char	*find_varname(char *str)
{
	char	*ptr_to_equal;
	char	*var_name;

	ptr_to_equal = ft_strchr(str, '=');
	if (ptr_to_equal == 0)
		var_name = ft_substr(str, 0, ft_strlen(str));
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

void	run_export_keyword(char	*str, t_shell *shell_info, int *status)
{
	char		*var_name;
	char		*var_value;
	t_env_mini	*env_mini;
	char		*ptr;

	ptr = export_rm_quote(str);
	var_name = find_varname(ptr);
	var_value = find_varvalue(ptr);
	if (!var_name || !is_al_num_underscore(var_name) || \
	((ft_strlen(ptr)) && (ft_isdigit(*ptr))))
		run_export_keyword_error(status, var_name, var_value, ptr);
	else if (is_al_num_underscore(var_name))
	{
		env_mini = ft_lstnew_envmini(var_name, var_value);
		ft_lstlast_envmini(shell_info->env_mini)->next = env_mini;
		if (ptr)
			free_set_null(ptr);
	}
}

void	run_export(char *str, t_shell *shell_info)
{
	char	*inpt;
	char	**keywords;
	int		status;
	int		i;

	inpt = str;
	i = 0;
	status = 0;
	keywords = NULL;
	if (!str || !ft_strlen(inpt))
		run_declare_env(shell_info);
	else
	{
		keywords = ft_split(inpt, ' ');
		while (keywords && keywords[i])
		{
			run_export_keyword(keywords[i], shell_info, &status);
			i++;
		}
		free_split_set_null(keywords);
	}
	if (status)
		proc_exit(1, shell_info);
	else
		proc_exit(0, shell_info);
}
