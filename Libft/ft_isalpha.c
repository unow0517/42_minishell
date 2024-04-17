/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:20:45 by yowoo             #+#    #+#             */
/*   Updated: 2023/10/17 12:30:06 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

// int ft_isalpha(int c)
// {
//     if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
//         return 1;
//     else
//         return 0;
// }
// #include <stdio.h>
// int main(){
//     // if(ft_isalpha('1') == 1)
//     //     printf("c is alpha");
//     // else
//     //     printf("c is not alpha");
//     int result = ft_isalpha_2('a');
//     printf("%d", result);
// }