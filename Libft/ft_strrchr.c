/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:40:33 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/26 15:22:53 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*ptr;
	int		i;

	ptr = (char *) str;
	i = 0;
	while (ptr[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (ptr[i] == (char)c)
			return (ptr + i);
		i--;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>

// int main () {
//    const char str[] = "https://www.tutorialspoint.com";
//    const char ch = 'o';
//    char *ret;

//    ret = strrchr(str, ch);

//    printf("String after |%c| is - |%s|\n", ch, ret);

//    char* ft_ret;

//    ft_ret = ft_strrchr(str,ch);

//    printf("String after |%c| is - |%s|\n", ch, ft_ret);
//    return(0);
// }