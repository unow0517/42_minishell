/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:45:50 by tsimitop          #+#    #+#             */
/*   Updated: 2024/03/26 16:01:33 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_arguments(va_list ptr, char flag)
{
	int	bytes;

	bytes = 0;
	if (flag == 's')
		bytes = ft_putstr_fd(va_arg(ptr, char *), 1);
	else if (flag == 'd' || flag == 'i')
		bytes = ft_putnbr_fd(va_arg(ptr, int), 1);
	else if (flag == 'c')
		bytes = ft_putchar_fd(va_arg(ptr, int), 1);
	else if (flag == '%')
		bytes = ft_putchar_fd('%', 1);
	else if (flag == 'x')
		bytes = ft_puthexlow_fd(va_arg(ptr, unsigned int), 1);
	else if (flag == 'X')
		bytes = ft_puthexup_fd(va_arg(ptr, unsigned int), 1);
	else if (flag == 'u')
		bytes = ft_putunsign_fd(va_arg(ptr, unsigned int), 1);
	else if (flag == 'p')
		bytes = ft_putptr_fd(va_arg(ptr, void *), 1);
	else
		return (0);
	return (bytes);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		bytes;
	int		total_bytes;

	i = 0;
	bytes = 0;
	total_bytes = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			bytes = ft_arguments(ap, str[i]);
		}
		else
			bytes = ft_putchar_fd(str[i], 1);
		if (bytes == -1)
			return (va_end(ap), bytes);
		i++;
		total_bytes += bytes;
	}
	return (va_end(ap), total_bytes);
}
// #include <stdio.h>
// #include <stdlib.h>

// int main(int argc, char **argv)
// {
// 	// int i = 99999999999999999999;
// 	// // int *j;
// 	// ft_printf("HELLO %d %i %f\n", i, d, a);
// 	// j = &i;
// 	// char	*str;
// 	(void)argc;
// 	// str = "oxi allo karvouno";
// 	printf("%i\n", printf("%i\n", atoi(argv[1])));
// 	ft_printf("%i\n", ft_printf("%i\n", atoi(argv[1])));
// 	// printf("%d\n", printf("%s\n", str));
// 	// ft_printf("%d\n", ft_printf("%s\n", str));
// 	// printf("%d\n", printf("%u\n", i));
// 	// ft_printf("%d\n", ft_printf("%u\n", i));
// 	return (0);
// }

	// if (ft_putchar_fd(va_arg(ptr, int), 1) == -1)
	// 	return (-1);