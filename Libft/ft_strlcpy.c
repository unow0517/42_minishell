/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:43:49 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/30 13:04:19 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, unsigned int n)
{
	size_t	result;
	char	*srcp;

	srcp = (char *)src;
	while (*srcp != '\0' && n >= ft_strlen(src) + 1)
		*dst++ = *srcp++;
	if (*srcp == '\0')
	{
		*dst = '\0';
		result = ft_strlen(src);
	}
	if (n == 0)
		return (ft_strlen(src));
	while (*srcp != '\0' && n < ft_strlen(src) + 1 && n)
	{
		*dst++ = *srcp++;
		n--;
	}
	if (n == 0)
	{
		*(dst - 1) = '\0';
		result = ft_strlen(src);
	}
	return (result);
}

//test dest is rrrrrr
//returns length of intended string;
//length is always needed
//when n = 0, return length, dest stays same. = PASS
//when n = 1, dest is ^@rrrrr
//when n > 1, dest is src, with length -1
//when n < length of dest, rest of dest should be kept
//length is including '\0'
// int main(){
//     int n = 0;
//     char src[50] = "aaa";
//     char dest[15] = "rrrrrr";
//     printf("n: %d\n",n);
//     printf("srclen: %lu\n\n",strlen(src));
//     printf("strlcpy: %lu\n",strlcpy(dest,src,n));
//     puts(dest);
//     char dest_1[15] = "rrrrrr";;
//     printf("ft_strlcpy: %lu\n",ft_strlcpy(dest_1,src,n));
//     puts(dest_1);
// }
//length should be returned in any case
//strlcpy = output is the length it tries to copy, 
//if dest is shorter than intended length => error
//content of dest has nothing to do with strlcpy