/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:01:12 by tsimitop          #+#    #+#             */
/*   Updated: 2023/11/25 16:00:32 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strdup() function allocates sufficient memory for a copy of the string
// s1, does the copy, and returns a pointer to it.
char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;
	size_t	len_s1cpy;

	len_s1cpy = ft_strlen(s1);
	i = 0;
	ptr = (char *)malloc(len_s1cpy + 1);
	if (ptr)
	{
		while (len_s1cpy > i)
		{
			ptr[i] = s1[i];
			i++;
		}
		ptr[i] = '\0';
	}
	return (ptr);
}

// why malloc instead of calloc (len_s1cpy, sizeof(char))= one block, strlen
// doesn't include \0