/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:51:25 by yowoo             #+#    #+#             */
/*   Updated: 2023/11/17 19:46:10 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_p(unsigned long ptr)
{
	int	res;
	int	i;

	i = ft_putstr("0x");
	if (i == -1)
		return (-1);
	ft_put_hex_u(ptr);
	res = hex_len_u(ptr);
	return (res + 2);
}


//address == 107(base 10)
//output = 0x6b(base 16)
//0x means number behind it is base 16

//012345689abcdef
//107 = 6 x 16 + 11(b) 