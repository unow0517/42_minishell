/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:31:29 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/21 02:18:49 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

static int	cntwords(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s != '\0')
	{
		if (*s != c && (*(s + 1) == c || *(s + 1) == '\0'))
			cnt++;
		s++;
	}
	return (cnt);
}

static int	get_start(const char *s, char c)
{
	int	cnt;

	cnt = 0;
	while (s[cnt] != '\0')
	{
		if (s[cnt] != c)
			return (cnt);
		cnt++;
	}
	return (cnt);
}

static int	get_len(const char *s, char c)
{
	int	cnt;

	cnt = 0;
	while (s[cnt] != '\0')
	{
		if (s[cnt] == c)
			return (cnt);
		cnt++;
	}
	return (cnt);
}

static char	**free_mem(char **s, int count)
{
	while (count >= 0)
	{
		free(s[count]);
		count--;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		cnt;
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	cnt = cntwords(s, c);
	array = malloc((cntwords(s, c) + 1) * sizeof(char *));
	// array = ft_calloc((cntwords(s, c) + 1), sizeof(char *));
	if (!array)
		return (0);
	while (i < cnt)
	{
		printf("start : %d\n", start);
		start = start + get_start(s + start, c);
		len = get_len(s + start, c);
		array[i] = ft_substr(s, start, len);
		printf("array[%d]: %s\n",i, array[i]);
		// if (array[i] == NULL)
		// {
		// 	printf("hello");
		// 	return (free_mem(array, i));
		// }
		start = start + len + 1;
		i++;
	}
	printf("i: %d\n",i);
	array[i] = "\0";
	printf("array: %s\n",array[0]);
	printf("array: %s\n",array[1]);
    printf("array: %s\n",array[2]);
	return (array);
}

int main(){
    char string[] = "asdhk  slajf asd";
    char delim = ' ';
    char **token = ft_split(string, delim);
    int i = 0;
    // printf("res: %s\n",token[0]);
	// printf("res: %s\n",token[1]);
    // printf("res: %s\n",token[2]);

	// while(token[i] != 0)
	// {
    //    	printf("res: %s\n",token[i]);
    //     i++;
    // }
	return 0;
}