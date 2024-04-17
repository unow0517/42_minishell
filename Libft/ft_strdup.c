/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:24:07 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/30 12:37:49 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	result = (char *)malloc((ft_strlen(src)+1) * sizeof(char));
	if (!result)
		return (0);
	while (src[i] != '\0')
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	j = 0;
	if (src[j] == '\0')
		result[j] = '\0';
	return (result);
}

// int main(){
//     char src[] = "lorem ipsum dolor sit amet";
//     char* target = strdup(src);
//     char* target_1 = ft_strdup(src);

//     printf("target: %s\n", target);
//     printf("target_1: %s\n", target_1);
//     // printf("target[0]: %c\n", target[0]);
//     free(target_1);
//     // printf("target[0]_after free: %c\n", *target_1);
//     return 0;
// }