/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 18:12:08 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:42:57 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	trim(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

// Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
// specified in ’set’ removed from the beginning and the end of the string.
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*copy1;
	size_t	i;
	size_t	j;
	size_t	len_s1;

	j = 0;
	i = 0;
	len_s1 = ft_strlen(s1);
	while (s1[j] && trim(set, s1[j]))
		j++;
	while (len_s1 > 0 && trim(set, s1[len_s1 - 1]))
		len_s1--;
	if (j >= len_s1)
		return (ft_strdup(""));
	copy1 = (char *)malloc(len_s1 - j + 1);
	if (!copy1)
		return (NULL);
	while (len_s1 > j)
	{
		copy1[i] = s1[j];
		i++;
		j++;
	}
	copy1[i] = '\0';
	return (copy1);
}
// #include <stdio.h>
// int main(void)
// {
// 	char const *s1;
// 	char const *set;

// 	s1 = "";
// 	set = "";
// 	printf("%s\n%s", s1, set);
// 	printf("%s\n", ft_strtrim(s1, set));
// }
//without len_s1 > 0 doesnt work with """" input - line 43
/*
Parameters 			s1: The string to be trimmed.
					set: The reference set of characters to trim.
Return value 		The trimmed string.
					NULL if the allocation fails.
External functs. 	malloc
Description 		Allocates (with malloc(3)) and returns a copy of
					’s1’ with the characters specified in ’set’ removed
					from the beginning and the end of the string.
*/