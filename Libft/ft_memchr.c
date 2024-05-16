/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 07:26:46 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/18 18:43:43 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memchr(const void *str, int c, unsigned int n)
{
	char	*ptr;

	ptr = (char *)str;
	while (n--)
	{
		if (*ptr == (char)c)
			return (ptr);
		else
			ptr++;
	}
	return (0);
}

//different between memchr vs strchr : 
//memchr compares regardless of null terminator
// #include <stdio.h>
// #include <string.h>
// int main(){
//     char str[] = "I am Coding\0\0KK";
//     char letter = 'K';
//     int len = 50;
//     char* res = memchr(str, letter, len);
// 	// char* res = memchr(s, 258, 3);
//     printf("String after |%c| is - |%s|\n",letter,res);
//     char* myRes = ft_memchr(str, letter, len);
// 	// char* myRes = ft_memchr(s, 258, 3);
//     printf("String after |%c| is - |%s|\n",letter,myRes);
//     return 0;  
// }
