/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:05:25 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/17 18:53:15 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

int	ft_strncmp(const char *str1, const char *str2, unsigned int n)
{
	unsigned char	*str1_1;
	unsigned char	*str2_1;

	str1_1 = (unsigned char *)str1;
	str2_1 = (unsigned char *)str2;
	while ((*str1_1 != '\0' || *str2_1 != '\0') && n--)
	{
		if (*str1_1 != *str2_1)
			return (*str1_1 - *str2_1);
		else
		{
			str1_1++;
			str2_1++;
		}
	}
	return (0);
}

//char value range (-128 ~ 127  or 0 to 255)
//unsigned char value range ( 0 to 255)
// int main () {
//     char str1[15];
//     char str2[15];
//     int ret;
//     int myRet;
//     strcpy(str1, "test\200");
//     strcpy(str2, "test\0");
//     ret = strncmp(str1, str2, 6);
//     myRet = ft_strncmp(str1, str2, 6);
//     printf("ret value is: %d\n", ret);
//     printf("myRet value is: %d", myRet);
//     return(0);
// }

//find the first different elemnt and get the value