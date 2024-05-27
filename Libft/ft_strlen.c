/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:12:26 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:42:39 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
// strlen does not do a NULL check (NULL edge case), results in seg fault
//-> if (str == NULL) return (0)
// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char *str = "food";
// 	printf("%lu", ft_strlen(str));
// 	printf("\n");
// 	printf("%lu", strlen(str));
// 	printf("\n");
// 	//str = NULL;
// 	printf("%lu", ft_strlen(str));
// 	printf("\n");
// 	printf("%lu", strlen(str));
// 	return (0);
// }
