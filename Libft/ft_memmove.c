/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:20:33 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/17 14:20:20 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*s;
	char		*d;

	s = (char *)src;
	d = (char *)dst;
	if (!d && !s)
		return (NULL);
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else if (d > s)
	{
		d = d + len - 1;
		s = s + len - 1;
		while (len--)
			*d-- = *s--;
	}
	return (dst);
}

// int main(){
//     const char src[50] = "SrcSrcSrc";
//     char dest[50];
//     strcpy(dest,"DestDestDest");
//     printf("Before memmove dest = %s\n", dest);
//     memmove(dest, src, strlen(src)+1);
//     printf("After memmove dest = %s\n\n", dest);
//     const char src_1[50] = "SrcSrcSrc";
//     char dest_1[50];
//     strcpy(dest_1,"DestDestDest");
//     printf("Before ft_memmove dest = %s\n", dest_1);
//     ft_memmove(dest_1, src_1, strlen(src_1)+1);
//     printf("After ft_memmove dest = %s\n", dest_1);
// }