/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:54:26 by tsimitop          #+#    #+#             */
/*   Updated: 2023/11/18 15:45:32 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fd(long n, int fd)
{
	char	digit;
	int		bytes;
	int		total_bytes;

	total_bytes = 0;
	if (n < 0)
	{
		if (ft_putchar_fd('-', fd) == -1)
			return (-1);
		total_bytes++;
		n = -n;
	}
	if (n / 10 > 0)
	{
		bytes = ft_putnbr_fd(n / 10, fd);
		if (bytes == -1)
			return (-1);
		total_bytes += bytes;
	}
	digit = (n % 10) + '0';
	bytes = ft_putchar_fd(digit, fd);
	if (bytes == -1)
		return (-1);
	total_bytes += bytes;
	return (total_bytes);
}
