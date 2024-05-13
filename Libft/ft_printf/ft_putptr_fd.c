/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:59:50 by tsimitop          #+#    #+#             */
/*   Updated: 2023/11/18 15:57:43 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_longhex(long n, int fd)
{
	char		*str;
	static int	bytes;
	static int	total_bytes;

	bytes = 0;
	total_bytes = 0;
	str = "0123456789abcdef";
	if (n / 16 > 0)
		ft_longhex(n / 16, fd);
	bytes = ft_putchar_fd(str[n % 16], fd);
	if (bytes == -1)
		return (bytes);
	total_bytes += bytes;
	return (total_bytes);
}

int	ft_putptr_fd(void *ptr, int fd)
{
	uintptr_t	uintptr;
	char		*str;
	int			byte_2;
	int			total_bytes;
	int			null_byte;

	total_bytes = 0;
	null_byte = 0;
	uintptr = (uintptr_t)ptr;
	str = "0123456789abcdef";
	byte_2 = 2;
	if (ft_putstr_fd("0x", fd) == -1)
		return (-1);
	if (uintptr / 16 > 0)
	{
		null_byte = ft_longhex(uintptr / 16, fd);
		if (null_byte == -1)
			return (null_byte);
		total_bytes += null_byte;
	}
	null_byte = ft_putchar_fd(str[uintptr % 16], fd);
	if (null_byte == -1)
		return (null_byte);
	total_bytes += null_byte;
	return (total_bytes + byte_2);
}

// printf("\nbyte initialized = %d\n", byte);
// printf("\nbyte after sizehex = %d\n", byte);
// printf("\nbyte after putchar = %d\n", byte);