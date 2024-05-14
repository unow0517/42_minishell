/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 18:26:11 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/02 15:33:01 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

int	idx_start(const char *s1, const char *set)
{
	int		i;
	char	*s1_p;

	i = 0;
	s1_p = (char *)s1;
	while (s1_p[i] != '\0')
	{
		if (ft_strchr(set, s1_p[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

int	idx_end(const char *s1, const char *set)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	while (i < len)
	{
		if (ft_strchr(set, s1[len - 1 - i]) == 0)
			return (len - i - 1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*newstr;
	int		i_st;
	int		i_end;

	i_st = idx_start(s1, set);
	i_end = idx_end(s1, set);
	newstr = 0;
	if (s1[0] == '\0' || set[0] == '\0')
	{
		return (ft_strdup(s1));
	}
	if (i_st >= i_end && i_st == 0)
	{
		return (ft_strdup(""));
	}
	else if (idx_end - idx_start + 1 > 0)
		newstr = (char *)malloc(sizeof(char) * (i_end - i_st + 2));
	if (!newstr)
		return (0);
	ft_strlcpy(newstr, s1 + i_st, i_end - i_st + 2);
	return (newstr);
}

// int main(){
//     char s1[] = "";
//     char set[] = "";
//     char* res = ft_strtrim(s1, set);
//     int i_start = idx_start(s1, set);
// 	int i_end = idx_end(s1, set);

// 	printf("result: %s\n",res);
//     printf("idx_start: %d\n",i_start);
// 	printf("idx_end: %d",i_end);
//     return 0;
// }