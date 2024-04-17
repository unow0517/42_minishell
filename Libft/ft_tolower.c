/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:38:02 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/18 14:44:36 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c = c + 32;
	return (c);
}

// int main () {
//     int i = 0;
//     // char c;
//     char str[] = "TOTURIAL POINT";
//     while(str[i]) {
//         putchar (tolower(str[i]));
//         i++;
//     }
//     putchar('\n');
//     i = 0;
//     while(str[i]) {
//         putchar (ft_tolower(str[i]));
//         i++;
//     }
//     return(0);
// }