/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:24:17 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:42:51 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief This is the function to find a needle in a haystack
 * 
 * @param haystack string which will be searched
 * @param needle string to find
 * @param len length within it should search
 * @return char* Pointer to the start of the needle within the haystack or NULL
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_needle;

	i = 0;
	len_needle = ft_strlen(needle);
	if (ft_strncmp(needle, "", len_needle) == 0)
		return ((char *)haystack);
	if (ft_strncmp(haystack, "", len_needle) == 0)
		return (NULL);
	while (i + len_needle <= len)
	{
		if (ft_strncmp(haystack + i, needle, len_needle) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

// char *ft_strnstr(const char *haystack, const char *needle, size_t len)FINAL
// {
// 	size_t i;
// 	size_t len_needle;	
// 	i = 0;
// 	len_needle = ft_strlen(needle);
// 	if (ft_strncmp(needle, "", len_needle) == 0)
// 		return ((char *)haystack);
// 	if (ft_strncmp(haystack, "", len_needle) == 0)
// 		return (NULL);
// 	// if (len_needle == 0)
// 	// 	return (char *)haystack;	//this is useless
// 	while (i + len_needle <= len) //<=!!!
// 	{
// 		if (ft_strncmp(haystack + i, needle, len_needle) == 0) {
// 			// return (char *)(haystack + i);	chat gpt's
// 			return ((char *)haystack + i);		// mine (they are both right)
// 		}
// 		i++;
// 	}
// 	return NULL; // Needle not found
// }
// if (ft_strncmp(needle, "", len_needle) == 0) //if those 2 if's missing it 
// doesn't segfault, without this doesn't work with empty strings
	// return ((char *)haystack);
// if (ft_strncmp(haystack, "", len_needle) == 0) //second if
	// return (NULL);

// char	*ft_strnstr(const char *haystack, const char *needle, size_t len) //MINE
// {
// 	size_t i;
// 	size_t len_needle;

// 	i = 0;
// 	len_needle = ft_strlen(needle); // needs to be on top to segfault if it's
// 									NULL, pointer doesnt exist
// 	if (ft_strncmp(needle, "", len_needle) == 0)
// 		return ((char *)haystack);
// 	if (ft_strncmp(haystack, "", len_needle) == 0)
// 		return (NULL);
// 	// ft_strlen(haystack);	checks if it's empty -> MAKES NO DIFFERENCE
// 	if (haystack == needle)
// 		{
// 			if (ft_strncmp(haystack, needle, len_needle) == 0)
// 				return ((char *)haystack);
// 			if (ft_strncmp(haystack, needle, len_needle) != 0)
// 				return (NULL);
// 		}
// 	while (i + len_needle <= len)the <= was the problem, both functions work now
// 	{
// 		if (ft_strncmp(haystack + i, needle, len_needle) == 0)
// 			return ((char *)haystack + i);
// 		i++;
// 	}
// 	return (NULL);
// }