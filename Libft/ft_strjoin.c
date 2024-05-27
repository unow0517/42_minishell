/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:49:10 by tsimitop          #+#    #+#             */
/*   Updated: 2024/03/29 18:22:33 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocates (with malloc(3)) and returns a newstring, which is the result 
// of the concatenationof ’s1’ and ’s2’.
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return ((char *)s2);
	if (!s2)
		return ((char *)s1);
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!ptr)
		return (NULL);
	while (s1[i] != '\0')
		ptr[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		ptr[j++] = s2[i++];
	ptr[j] = '\0';
	return (ptr);
}

/*
Parameters 			s1: The prefix string.
					s2: The suffix string.
Return value 		The new string.
					NULL if the allocation fails.
External functs. 	malloc
Description 		Allocates (with malloc(3)) and returns a new
					string, which is the result of the concatenation
					of ’s1’ and ’s2’.

*/