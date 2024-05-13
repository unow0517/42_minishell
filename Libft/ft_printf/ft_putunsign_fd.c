/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsign_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:59:09 by tsimitop          #+#    #+#             */
/*   Updated: 2023/11/18 14:57:58 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsign_fd(unsigned int n, int fd)
{
	int			byte;
	static int	total_bytes;
	char		digit;

	byte = 0;
	total_bytes = 0;
	if (n / 10 > 0)
	{
		byte = ft_putnbr_fd(n / 10, fd);
		if (byte == -1)
			return (-1);
		total_bytes += byte;
	}
	digit = (n % 10) + '0';
	byte = ft_putchar_fd(digit, fd);
	if (byte == -1)
		return (byte);
	total_bytes += byte;
	return (total_bytes);
}
