/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:22:21 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:42:54 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The strrchr() function locates the last occurrence of c (converted to a char)
// in the string pointed to by s.
char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	last_occurence;

	i = 0;
	last_occurence = -1;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			last_occurence = i;
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	else if (last_occurence >= 0)
		return ((char *)&s[last_occurence]);
	return (NULL);
}
