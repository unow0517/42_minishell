/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexlow_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:56:41 by tsimitop          #+#    #+#             */
/*   Updated: 2023/11/18 15:47:17 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthexlow_fd(unsigned int n, int fd)
{
	char	*str;
	int		bytes;
	int		total_bytes;

	total_bytes = 0;
	bytes = 0;
	str = "0123456789abcdef";
	if (n / 16 > 0)
	{
		bytes = ft_puthexlow_fd(n / 16, fd);
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

// printf("n = %d             | [%d] = %c\n", n, n %16, str[n % 16]);