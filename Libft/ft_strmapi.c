/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:27:37 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:42:43 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Applies the function ’f’ to each character of the string ’s’, and passing
// its index as first argument to create a new string (with malloc(3)) resulting
// from successive applications of ’f’.
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*c;

	i = 0;
	if (!s || !f)
		return (NULL);
	c = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!c)
		return (NULL);
	while (s[i] != '\0')
	{
		c[i] = f(i, s[i]);
		i++;
	}
	c[i] = '\0';
	return (c);
}

/*
Parameters 			s: The string on which to iterate.
					f: The function to apply to each character.
Return value 		The string created from the successive applications of ’f’.
					Returns NULL if the allocation fails.
External functs. 	malloc
Description 		Applies the function ’f’ to each character of the
					string ’s’, and passing its index as first argument
					to create a new string (with malloc(3)) resulting
					from successive applications of ’f’.
*/