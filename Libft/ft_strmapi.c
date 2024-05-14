/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 09:56:13 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/30 13:04:52 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (0);
	while (*s)
	{
		*(res + i) = f(i, *s++);
		i++;
	}
	*(res + i) = '\0';
	return (res);
}

// int main(void)
// {
// 	char	*res;
// 	char	*str;

// 	str = "Hello World";
// 	res = ft_strmapi(str, my_toupper);
// 	printf("res: %s", res);
// 	return (0);
// }