/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 20:58:56 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:40:57 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The atoi() function converts the initial portion of the string pointed to by
// str to int representation.
int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == ' ' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' || str[i] == '+')
			if (str[i] == '-')
				sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}
// #include <stdio.h>
// #include <stdlib.h>

// int	main(void)
// {
// 	const char	*str = "   -978uio";

// 	printf("%d", ft_atoi(str));
// 	return (0);
// }