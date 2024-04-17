/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:20:54 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/17 14:25:21 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_memset(void *str, int c, unsigned int n)
{
	char	*p;

	p = (char *)str;
	while (n > 0)
	{
		*p = c;
		p++;
		n--;
	}
	return (str);
}

// #include "libft.h"
// #include <stdio.h>
// #include <string.h>
// int main () {
//     char str[50] = "today is wednesday";
//     // char example[] = "15";

//     //strcpy(example,"123123123123123");
//     puts(str);

//     ft_memset(str,'A','!');
//     puts(str);
//     return(0);
// }