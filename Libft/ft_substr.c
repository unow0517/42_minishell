/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 19:47:07 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:43:01 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocates (with malloc(3)) and returns a substring from the string ’s’. The
// substring begins at index ’start’ and is of maximum size ’len’.
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	i;
	size_t	len_create;
	size_t	len_s;

	i = 0;
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if (len_s - start < len)
		len_create = len_s - start;
	else
		len_create = len;
	cpy = (char *)malloc(len_create + 1);
	if (!cpy)
		return (NULL);
	while (s[start + i] != '\0' && i < len_create)
	{
		cpy[i] = s[start + i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

// #include <stdio.h>

// int main(void)
// {
// 	char const *s = "poignant roses making weird curtains";
// 	unsigned int start = 40;
// 	size_t len = 50;
// 	printf("with start 40 %s\n", ft_substr(s, start, len));
// 	return (0);
// }
/*
Function name 	ft_substr
Prototype 		char *ft_substr(char const *s, unsigned int start, size_t len);
Turn in files 	-
Parameters 		s: The string from which to create the substring.
				start: The start index of the substring in the string ’s’.
				len: The maximum length of the substring.
Return value 	The substring.
				NULL if the allocation fails.
External fncs.	malloc
Description		Allocates (with malloc(3)) and returns a substring from the
				string ’s’.
				The substring begins at index ’start’ and is of
				maximum size ’len’.
*/