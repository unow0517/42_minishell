/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:44:57 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/26 15:05:42 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char *src, unsigned int size)
{
	unsigned int	result;
	unsigned int	i;
	unsigned int	j;

	result = 0;
	i = 0;
	while (dst[i] != '\0')
	{
		result++;
		i++;
	}
	j = 0;
	while (src[j] != '\0' && i < size -1 && size)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	while (src[j] != '\0')
		j++;
	if (size < i)
		return (ft_strlen(src) + size);
	return (result + ft_strlen(src));
}

// int main(){
//     int size = 0;
//     printf("size: %d\n",size);
//     char dStr[30] = "rrrrrr\0\0\0\0a\0\0\0\0";
//     // char dStr[30] = "pqrstuvwxyz";
//     char sStr[] = "lorem ipsum dolor sit amet"; 
//length 26 without null term.
//     printf("lensum: %lu\n\n", ft_strlen(dStr) + ft_strlen(sStr));

//     int res = strlcat(dStr, sStr, size);
//     printf("res is: %d\n", res);
//     printf("dest is: %s\n", dStr);

//     char dStr_1[30] = "rrrrrr\0\0\0\0a\0\0\0\0";
//     // char dStr_1[30] = "pqrstuvwxyz";
//     char sStr_1[] = "lorem ipsum dolor sit amet";

//     int res_1 = ft_strlcat(dStr_1, sStr_1, size);
//     printf("myres is: %d\n", res_1);
//     printf("mydest is: %s\n", dStr_1);
//     return 0;
// }

//return value = length sum of dStr, sStr
//len is to be # of letter in dest - 1.
//dest should be same or bigger than len, otherwise error(illegal instruction)