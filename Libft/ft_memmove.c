/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:25:55 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/29 13:30:32 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The memmove() function copies len bytes from string src to string dst.
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*source;

	dest = (unsigned char *) dst;
	source = (unsigned char *) src;
	if (dst == src)
		return (dst);
	if (dst < src)
	{
		while (0 < len--)
			*dest++ = *source++;
	}
	if (dst > src)
	{
		{
			dest += len;
			source += len;
			while (len-- > 0)
				*(--dest) = *(--source);
		}
	}
	return (dst);
}
// #include <stdio.h>

// int main(void)
// {
// 	//overlap case
// 	// char dst[] ="oldstring";
// 	// const char src[] = "secondone";

// 	// printf("Before: dest = %p, dest = %s,
//  src = %p, src = %s,\n", dst, dst, src, src);
	// ft_memmove(dst, src, 5);

// 	// printf("After: dest = %p, dest = %s, 
// src = %p, src = %s,\n", dst, dst, src, src);

// 	// null case
// 	char dst[] ="          ";
// 	const char src[] = "      ";

// 	printf("Before: dest = %p, dest = %s, src = %p,
//  src = %s,\n", dst, dst, src, src);
// 	ft_memmove(dst, src, 5);

// 	printf("After: dest = %p, dest = %s, src = %p, 
// src = %s,\n", dst, dst, src, src);
// 	return (0);
// }
