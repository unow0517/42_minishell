/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_subfns_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 09:57:55 by yowoo             #+#    #+#             */
/*   Updated: 2023/11/03 10:10:31 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_writenbr(int n)
{
	int	output;
	int	i;

	output = n + 48;
	i = write(1, &output, 1);
	if (i == -1)
		return (-1);
	return (i);
}

int	ft_putnbr(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	else if (n < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		ft_putnbr(-n);
	}
	else if (n >= 10)
	{
		i += ft_putnbr(n / 10);
		if (i <= -1)
			return (-1);
		ft_putnbr(n % 10);
	}
	else
	{
		if (ft_writenbr(n) == -1)
			return (-1);
	}
	return (i);
}

// size_t	ft_strlen(const char *str)
// {
// 	unsigned int	len;

// 	len = 0;
// 	while (*str != '\0')
// 	{
// 		len++;
// 		str++;
// 	}
// 	return (len);
// }

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		i = write(1, s, 1);
		if (i == -1)
			return (-1);
		s++;
	}
	return (i);
}
