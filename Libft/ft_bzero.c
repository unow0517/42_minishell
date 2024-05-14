/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:41:54 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/30 13:09:25 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, unsigned int n)
{
	unsigned char	*p;

	p = str;
	while (n > 0)
	{
		*p = '\0';
		p++;
		n--;
	}
}

// #include <stdio.h>
// #include <string.h>
// int main(){
//     char str[50];

//     strcpy(str,"This is string.h library function@@!");
//     puts(str);

//     ft_bzero(str,7);
//     puts(str+7);
//     return(0);
// }
//bzero does not return value