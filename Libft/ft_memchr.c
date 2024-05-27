/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:44:54 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:41:42 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
#include "libft.h"

// The memchr() function locates the first occurrence of c
// (converted to an unsigned char) in string s.
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (n-- > 0)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (NULL);
}
// int main(void)
// {
// 	char str[50] = "'Let's talk about the weather'";
// 	memchr(str, 't', 8);
// 	printf("After memset: %s\n", str);
// 	return (0);
// }
// while (n-- > 0 && str[i] != '\0') //str[i] != '\0' && 