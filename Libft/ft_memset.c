/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:59:00 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:41:56 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The memset() function writes len bytes of value c
// (converted to an unsigned char) to the string b.
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*uc;

	i = 0;
	uc = b;
	while (i < len)
	{
		uc[i] = c;
		i++;
	}
	return (uc);
}

//i < len - 1????
// int main(void)
// {
// 	char str[50] = "'Let's talk about the weather'";
// 	printf("%s is the sentence before memset\n", str);
// 	memset(str + 5, '&', 8);
// 	printf("After memset: %s\n", str);
// 	return (0);
// }