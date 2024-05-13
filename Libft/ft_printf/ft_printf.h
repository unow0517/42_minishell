/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 13:42:17 by tsimitop          #+#    #+#             */
/*   Updated: 2023/11/18 15:07:30 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *str, ...);
int	ft_putstr_fd(char *s, int fd);
int	ft_putnbr_fd(long n, int fd);
int	ft_putchar_fd(char c, int fd);
int	ft_puthexlow_fd(unsigned int n, int fd);
int	ft_puthexup_fd(unsigned int n, int fd);
int	ft_putunsign_fd(unsigned int n, int fd);
int	ft_putptr_fd(void *ptr, int fd);

#endif