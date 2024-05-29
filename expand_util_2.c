/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:33:41 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/29 14:36:45 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	if (*str == '$' && !*i_sq)
	{
		till_d = ft_substr(shell_info->user_input, 0, \
		str - start);
		l = ft_varname_len(str);
		v = ft_varvalue(l, str, shell_info->env_mini);
		shell_info->user_input = ft_strjoin(till_d, replace_exp(str, v, l));
	}
}
