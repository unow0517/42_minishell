/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:03:49 by yowoo             #+#    #+#             */
/*   Updated: 2023/11/03 10:02:46 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_int(int n)
{
	int	res;
	int	i;

	i = 0;
	if (n == -2147483648)
		res = 11;
	else if (n < 0)
		res = dec_len_uint(-n) + 1;
	else
		res = dec_len_uint(n);
	i = ft_putnbr(n);
	if (i == -1)
		return (-1);
	return (res);
}
