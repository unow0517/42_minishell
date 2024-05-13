/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:53:15 by tsimitop          #+#    #+#             */
/*   Updated: 2023/11/18 14:47:42 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	null_case(int fd)
{
	char	*str_null;
	int		j;
	int		byte;
	int		total_bytes;

	str_null = "(null)";
	j = 0;
	byte = 0;
	total_bytes = 0;
	while (str_null && str_null[j] != 0)
	{
		byte = ft_putchar_fd(str_null[j++], fd);
		if (byte == -1)
			return (-1);
		total_bytes += byte;
	}
	return (total_bytes);
}

int	ft_putstr_fd(char *s, int fd)
{
	int		i;
	int		byte;
	int		total_bytes;

	byte = 0;
	i = 0;
	total_bytes = 0;
	if (!s)
		total_bytes = null_case(fd);
	while (s && s[i] != 0)
	{
		byte = ft_putchar_fd(s[i++], fd);
		if (byte == -1)
			return (-1);
		total_bytes += byte;
	}
	return (total_bytes);
}
