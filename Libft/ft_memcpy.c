/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:31:14 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:41:48 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The memcpy() function copies n bytes from memory area src to memory area dst.
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	size_t	j;
	char	*dest;
	char	*source;

	i = 0;
	j = 0;
	dest = (char *)dst;
	source = (char *)src;
	if (src == 0 && dst == 0)
		return (0);
	while (j < n)
	{
		dest[i] = source[j];
		i++;
		j++;
	}
	return (dst);
}
