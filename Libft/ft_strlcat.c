/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:38:24 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:42:32 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	i = 0;
	j = 0;
	if (dstlen >= dstsize)
		return (srclen + dstsize);
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && (i + 1) < dstsize)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (srclen + dstlen);
}
// #include <stdio.h>
// int main()
// {
// 	char	dest[30];
// 	ft_memset(dest, 0, 30);
// 	char * src = (char *)"BBBB";
// 	dest[0] = 'B';
// 	size_t x = ft_strlcat(dest, src, 3);
// 	// size_t x = strlcat(dest, src, 6);
// 	printf("%s\n%lu", dest, x);
// }