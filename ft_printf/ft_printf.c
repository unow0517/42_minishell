/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:33:57 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/15 12:00:20 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	arglist;
	int		cnt;
	int		temp;

	va_start(arglist, format);
	cnt = 0;
	if (*format == 0 || format == 0)
		return (0);
	while (*format != '\0')
	{
		if (*format != '%')
			temp = ft_printf_c(*format);
		else
			temp = ft_specifiers(++format, arglist);
		if (temp == -1)
		{
			va_end(arglist);
			return (-1);
		}
		format++;
		cnt += temp;
	}
	va_end(arglist);
	return (cnt);
}

// int	main(void)
// {
// 	// int        *ptr;
//     // int     test = 80;
// 	// ptr = &test;
//     // unsigned long i = (unsigned long)ptr;
//     // printf("1-> %p\n", "50");≤
// 	// printf("i-> %lu", i);
//     // ft_printf("my-> %p\n", "50");
// 	int	res1;
// 	int	res;
// 	res1 = ft_printf("%p", "-10");
// 	printf("%c",'\n');
// 	res = printf("%d %d %d", "-10", "5", "5");
// 	printf("\nreturnmy:%d",res1);
// 	printf("\nreturn:%d",res);
// 	return (0);
// }
