/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:38:50 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:41:39 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// #include <stdio.h>

static int	ft_nlen(int n);

// Allocates (with malloc(3)) and returns a string representing the integer
// received as an argument. Negative numbers must be handled.
char	*ft_itoa(int n)
{
	char	*copy;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_nlen(n);
	copy = (char *)malloc(len + 1);
	if (!copy)
		return (NULL);
	if (n < 0)
	{
		n = -n;
		copy[0] = '-';
	}
	copy[len] = '\0';
	while (n > 0)
	{
		copy[len - 1] = (n % 10) + '0';
		len--;
		n /= 10;
	}
	return (copy);
}

static int	ft_nlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0 && n != -2147483648)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}
// int main(void)
// {
// 	int n;
// 	n = 456;

// 	// printf("%d", ft_nlen(n));
// 	printf("%s", ft_itoa(n));
// 	return (0);
// }

// printf("\n%s\n", copy);
// printf("copy[%d] = %c\n",len - 1 ,copy[len - 1]);
// printf("n = %d\n len = %d\n", n, len);
/*
Parameters 			n: the integer to convert.
Return value 		The string representing the integer.
					NULL if the allocation fails.
External functs. 	malloc
Description 		Allocates (with malloc(3)) and returns a string
					representing the integer received as an argument.
					Negative numbers must be handled.
*/