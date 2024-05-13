/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:42:08 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:42:36 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// strlcpy() copies up to dstsize - 1 characters from the string src to dst,
// NUL-terminating the result if dstsize is not 0.
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = 0;
	if (dstsize != 0)
	{
		while (i < dstsize - 1 && i < len)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (len);
}

// size_t	ft_strlen(const char *str);

// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	i;

// 	i = 0;
// 	if (dstsize == '\0')
// 	{
// 		dst[i] = '\0';
// 	}
// 	while (i < (dstsize - 1) && (dstsize > '\0') && src[i] != '\0')
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (ft_strlen(src));
// }

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// // 	char	s1[61] = "small sentence";
// // 	char	s2[15] = "larger sentence";
// 	// char dest[14] = "a";
// 	char dest[10];
// 	memset(dest, 'A', 10);

// 	// ssize_t ho = strlcpy(dest, "coucou", -1);
// 	// printf("%lu\n%s\n\n", ho, dest);
// 	ssize_t	hi = ft_strlcpy(dest, "coucou", -1);
// 	printf("%lu\n%s\n\n", hi, dest);
// 	printf("%d\n%d\n\n", (dest[0] == 'c'), dest);
// 	if (dest[0] == 'c' && dest[1] == 0  && dest[2] == 'A')

// 	return (0);
// }

// size_t	ft_strlen(const char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		i++;
// 	}
// 	return (i);
// }
