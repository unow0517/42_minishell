/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:17:21 by yowoo             #+#    #+#             */
/*   Updated: 2023/11/03 09:38:54 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	hex_len_int(int n)
{
	int	len;

	if (n < 0)
		return (8);
	len = 0;
	if (n < 0)
	{
		len = 1;
		n = -n;
	}
	while (n >= 16)
	{
		len++;
		n = n / 16;
	}
	len++;
	return (len);
}

int	ft_printf_x(unsigned int n, const char *format)
{
	int	res;
	int	i;

	i = 0;
	if (*format == 'x')
	{
		i = ft_put_hex_u(n);
		if (i == -1)
			return (-1);
	}
	else if (*format == 'X')
	{
		i = ft_put_hexbig_u(n);
		if (i == -1)
			return (-1);
	}
	res = hex_len_int(n);
	if (i == -1)
		return (-1);
	return (res);
}
