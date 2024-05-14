/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:34:14 by yowoo             #+#    #+#             */
/*   Updated: 2023/11/03 10:11:06 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "libft/libft.h"

int		ft_printf(const char *format, ...);

//functions
int		ft_printf_c(char c); // for c, %
int		ft_printf_s(char *s);
int		ft_printf_p(unsigned long ptr);
int		ft_printf_int(int n);
int		ft_printf_u(unsigned int num);
int		ft_printf_x(unsigned int n, const char *format);// for x, X

//specifier cases
int		ft_specifiers(const char *format, va_list argslist);

//subfns_1
//writenbr for putnbr
int		ft_putnbr(int n); //for int, s, u
size_t	ft_strlen(const char *str); //for s
int		ft_putstr(char *s); //for p, u

//subfns_2
int		hex_len_u(unsigned long n); // for p
int		dec_len_uint(unsigned int n); // for int, putintplus -> u, u
int		ft_put_hex_u(unsigned long n);// for p, x
int		ft_put_hexbig_u(unsigned long n); // for x
