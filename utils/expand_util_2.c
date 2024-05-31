/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:33:41 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/31 09:19:44 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cpy_str(char *str, char *dst, int cnt)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == '^')
		{
			dst[j] = '$';
			i++;
		}
		else if (str[i] == '^' && str[i + 1] == '\\')
		{
			dst[j] = '$';
			i++;
		}
		else
			dst[j] = str[i];
		j++;
		i++;
	}
	dst[ft_strlen(str) - cnt] = '\0';
}

void	update_quoted(char *str, int *i_sq)
{
	if (*str == '\'')
	{
		if (!*i_sq)
			*i_sq = 1;
		else
			*i_sq = 0;
	}
}

void	exp_shell(char *str, int *i_sq, char *start, t_shell *shell_info)
{
	char	*till_d;
	int		l;
	char	*v;
	char	*to_replace;

	if (*str == '$' && !*i_sq)
	{
		till_d = ft_substr(shell_info->user_input, 0, \
		str - start);
		l = ft_varname_len(str);
		v = ft_varvalue(l, str, shell_info->env_mini);
		free(shell_info->user_input);
		shell_info->user_input = NULL;
		to_replace = replace_exp(str, v, l);
		shell_info->user_input = ft_strjoin(till_d, to_replace);
		free(to_replace);
		to_replace = NULL;
		free(till_d);
		till_d = NULL;
	}
}
