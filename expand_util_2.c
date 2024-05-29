/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:33:41 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/29 11:45:12 by yowoo            ###   ########.fr       */
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
