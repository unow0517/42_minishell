/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:01:47 by yowoo             #+#    #+#             */
/*   Updated: 2023/11/02 15:08:12 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_s(char *s)
{
	int	len;
	int	i;

	if (s == 0)
	{
		i = ft_putstr("(null)");
		if (i == -1)
			return (-1);
		return (6);
	}
	i = ft_putstr(s);
	if (i == -1)
		return (-1);
	len = ft_strlen(s);
	return (len);
}
