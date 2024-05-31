/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:20:35 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/31 09:09:49 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_al_num_udsc_c(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	ft_varname_len(char *str)
{
	int	i;

	i = 0;
	while (*str && str)
	{
		if (*str == '$')
		{
			str++;
			while (is_al_num_udsc_c(*str))
			{
				i++;
				str++;
			}
			if (!is_al_num_udsc_c(*str))
				break ;
		}
		str++;
	}
	return (i);
}

char	*ft_varvalue(int var_name_len, char *str, t_env_mini *env_mini)
{
	char	*ptr_dollar;
	char	*varname;

	ptr_dollar = ft_strchr(str, '$');
	varname = 0;
	if (!ptr_dollar)
		return (0);
	varname = ft_substr(ptr_dollar + 1, 0, var_name_len);
	while (env_mini)
	{
		if (inputis(env_mini->name, varname))
		{
			free(varname);
			varname = NULL;
			return (env_mini->value);
		}
		if (env_mini->next)
			env_mini = env_mini->next;
		else
			break ;
	}
	free(varname);
	varname = NULL;
	return (0);
}

char	*join_three(char *str1, char *str2, char *str3)
{
	char	*join1;
	char	*join2;

	join1 = ft_strjoin(str1, str2);
	join2 = ft_strjoin(join1, str3);
	free(str1);
	str1 = NULL;
	free(join1);
	join1 = NULL;
	return (join2);
}

void	rm_ws_aft_dl(char *before, char *after, t_shell *shell_info)
{
	char	*join;
	char	*temp;

	if (before)
	{
		temp = before;
		before = rm_starting_ws(temp);
		free(temp);
		temp = NULL;
	}
	if (after && before)
	{
		join = ft_strjoin(before, after);
		free(before);
		before = NULL;
		free(shell_info->user_input);
		shell_info->user_input = NULL;
		shell_info->user_input = join;
	}
}
