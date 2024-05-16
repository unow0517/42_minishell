/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:39:46 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/03 17:24:53 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*res_ptr;

	result = (char *)malloc((ft_strlen(s1)+ft_strlen(s2)+1) * sizeof(char));
	if (!result)
		return (0);
	res_ptr = result;
	while (*s1 != '\0')
		*(res_ptr++) = *(s1++);
	while (*s1 == '\0' && *s2 != '\0')
		*(res_ptr++) = *(s2++);
	if (*s2 == '\0')
		*res_ptr = '\0';
	return (result);
}
// int main(){
//     char str[] = "";
//     char str1[] = "";
//     char* res = ft_strjoin(str,str1);
//     printf("Result:%s",res);
// }