/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:12:25 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/15 23:17:09 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if ((char)c == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}

// Allocates (with malloc(3)) and returns a newstring, which is the result 
// of the concatenation of ’s1’ and ’s2’.
char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ptr = (char *)ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof(char));
	if (!ptr)
		return (s1);
	while (s1[j] != '\0')
	{
		ptr[j] = s1[j];
		j++;
	}
	while (s2[i] != '\0')
		ptr[j++] = s2[i++];
	return (free(s1), ptr);
}

// The bzero() function writes n zeroed bytes to the string s.
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*uc;

	i = 0;
	uc = s;
	while (i < n)
	{
		uc[i] = 0;
		i++;
	}
}

// The calloc() function allocates memory and initializes all bits to zero.
void	*ft_calloc(size_t count, size_t size)
{
	int	*ptr;

	if (size == 0 || count == 0)
		return (NULL);
	else
	{
		ptr = malloc(size * count);
		if (!ptr)
			return (NULL);
		ft_bzero(ptr, size * count);
		return (ptr);
	}
}
