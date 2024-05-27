/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:57:11 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:42:24 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Applies the function ’f’ on each character of the string passed as argument,
// passing its index as first argument. Each character is passed by address to
// ’f’ to be modified if necessary.
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*
Parameters 			s: The string on which to iterate.
					f: The function to apply to each character.
Return value		None
External functs. 	None
Description 		Applies the function ’f’ on each character of
					the string passed as argument, passing its index
					as first argument. Each character is passed by
					address to ’f’ to be modified if necessary.
*/