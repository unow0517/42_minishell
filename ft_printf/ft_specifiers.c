/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:32:34 by yowoo             #+#    #+#             */
/*   Updated: 2023/11/03 09:44:21 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_specifiers(const char *format, va_list arglist)
{
	int	cnt;

	cnt = 0;
	if (*format == 'c')
		cnt = ft_printf_c(va_arg(arglist, int));
	else if (*format == 's')
		cnt = ft_printf_s(va_arg(arglist, char *));
	else if (*format == 'p')
		cnt = ft_printf_p(va_arg(arglist, unsigned long));
	else if (*format == 'd' || *format == 'i')
		cnt = ft_printf_int(va_arg(arglist, int));
	else if (*format == 'u')
		cnt = ft_printf_u(va_arg(arglist, unsigned int));
	else if (*format == 'x' || *format == 'X')
		cnt = ft_printf_x(va_arg(arglist, unsigned int), format);
	else if (*format == '%')
		cnt = ft_printf_c('%');
	else
		return (-1);
	return (cnt);
}
