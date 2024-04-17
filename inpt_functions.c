/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subfunctions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:24:13 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/17 11:24:14 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ifinputis(char *inpt, char *string)
{
	int	len;

	len = 0;
	if (ft_strlen(inpt) < ft_strlen(string))
		len = ft_strlen(string);
	else
		len = ft_strlen(inpt);
	if (ft_strncmp(inpt, string, len) == 0)
		return (1);
	else
		return (0);
}

int	ifinputstartswith(char *inpt, char *string)
{
	int	len;

	len = ft_strlen(string);
	if (ft_strncmp(inpt, string, len) == 0)
		return (1);
	else
		return (0);
}
