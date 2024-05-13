/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexup_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:24:50 by tsimitop          #+#    #+#             */
/*   Updated: 2023/11/18 15:47:34 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexup_fd(unsigned int n, int fd)
{
	char	*str;
	int		bytes;
	int		total_bytes;

	total_bytes = 0;
	bytes = 0;
	str = "0123456789ABCDEF";
	if (n / 16 > 0)
	{
		bytes = ft_puthexup_fd(n / 16, fd);
		if (bytes == -1)
			return (bytes);
		total_bytes += bytes;
	}
	bytes = (ft_putchar_fd(str[n % 16], fd));
	if (bytes == -1)
		return (bytes);
	total_bytes += bytes;
	return (total_bytes);
}
