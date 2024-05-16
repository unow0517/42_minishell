/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:20:30 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/17 13:50:18 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, unsigned int n)
{
	unsigned char		*pd;
	const unsigned char	*ps;

	pd = (unsigned char *)dest;
	ps = (const unsigned char *)src;
	if (pd == 0 && ps == 0)
		return (0);
	while (n)
	{
		*pd++ = *ps++;
		n--;
	}
	return (dest);
}

// in strcpy, dest length should be bigger than target, or error 

// int main(){
//     // const char src[50] = "SrcSrcSrc";
//     int len = 22;
//     const char src[] = "test basic du memcpy !";
//     char dest[22];
//     // strcpy(dest,"DestDestDest");
//     printf("Before memcpy dest = %s\n", dest);
//     // memcpy(dest, src, strlen(src)+1);
//     // memcpy(dest, src, len);
//     memcpy(((void *)0), ((void *)0), 0);

//     printf("After memcpy dest = %s\n\n", dest);

//     // const char src_1[50] = "SrcSrcSrc";
//     const char src_1[] = "test basic du memcpy !";
//     char dest_1[22];
//     // strcpy(dest_1,"DestDestDest");
//     printf("Before ft_memcpy dest = %s\n", dest_1);
//     // ft_memcpy(dest_1, src_1, strlen(src)+1);
//     // ft_memcpy(dest_1, src_1, len);
//     ft_memcpy(((void *)0), ((void *)0), 0);
//     printf("After ft_memcpy dest = %s\n", dest_1);

//     return(0);
// }
