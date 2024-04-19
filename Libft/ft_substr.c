/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:01:37 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/19 18:29:36 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slength;
	size_t	i;
	char	*ptr;

	i = 0;
	slength = ft_strlen(s);
	if (!s)
		return (NULL);
	if (len > slength - start)
		len = slength - start;
	if (start >= slength)
		return (ft_strdup(""));
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	ptr = substr;
	free(ptr);
	return (substr);
}
