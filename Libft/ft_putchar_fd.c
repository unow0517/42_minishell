/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:46:30 by tsimitop          #+#    #+#             */
/*   Updated: 2023/10/28 13:41:59 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Outputs the character ’c’ to the given file descriptor.
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
Parameters 			c: The character to output.
					fd: The file descriptor on which to write.
Return value 		None
External functs.	write
Description 		Outputs the character ’c’ to the given file
					descriptor.
*/