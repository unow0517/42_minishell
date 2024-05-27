/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:44:29 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:42:47 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// strncmp() function lexicographically compares the null-terminated strings s1
// and s2. Not more than n characters.
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	str1;
	unsigned char	str2;

	while (n-- > 0)
	{
		str1 = (unsigned char)*s1++;
		str2 = (unsigned char)*s2++;
		if (str1 != str2)
		{
			return (str1 - str2);
		}
		if (str1 == '\0')
		{
			return (0);
		}
	}
	return (0);
}
// str1 = (unsigned char)*s1++; it is needed within,
// can't declare and just call, it's not a function...
// (str1 == '\0') forces it to stop at '\0' else it doesn't stop