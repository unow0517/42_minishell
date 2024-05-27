/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:37:06 by tsimitop          #+#    #+#             */
/*   Updated: 2023/11/03 18:35:56 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Outputs the string ’s’ to the given file descriptor.
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		write(fd, &s[i++], 1);
}

/*
Parameters 			s: The string to output.
					fd: The file descriptor on which to write.
Return value 		None
External functs.	write
Description 		Outputs the string ’s’ to the given file descriptor.
*/