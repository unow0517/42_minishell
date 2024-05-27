/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:20:35 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/27 14:28:24 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*join_three(char *str1, char *str2, char *str3)
{
	char	*join1;
	char	*join2;

	join1 = ft_strjoin(str1, str2);
	join2 = ft_strjoin(join1, str3);
	free(join1);
	return (join2);
}