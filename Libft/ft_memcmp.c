/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 07:38:53 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/23 15:49:06 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_memcmp(const void *str1, const void	*str2, unsigned int n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *) str1;
	ptr2 = (unsigned char *) str2;
	while (n--)
	{
		if (*ptr1 != *ptr2)
			return (*ptr1 - *ptr2);
		else
		{
			ptr1++;
			ptr2++;
		}
	}
	return (0);
}
//different between memcmp vs strmcmp 
//: memcmp compares regardless of null terminator
//https://stackoverflow.com/questions/13095513/
//what-is-the-difference-between-memcmp-strcmp-and-strncmp-in-c
// #include <stdio.h>
// #include <string.h>
// int main(){
//     char str1[15] = "ABCDEF\0F";
//     char str2[15] = "ABCDEF\0f";
//     int res = memcmp(str1, str2, 15);
//     printf("memcmp is %d\n", res);
//     int myRes = ft_memcmp(str1,str2,15);
//     printf("ft_memcmp is %d", myRes);

//     return 0;
// }