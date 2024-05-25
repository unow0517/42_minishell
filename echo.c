/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:56:43 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/19 16:57:29 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_echo(char *inpt, t_shell *shell_info)
{
	// write(2, "HELLO\n", ft_strlen("HELLO\n"));
	//OPTION 1. WHEN THE WHOLE INPUT IS PASSED
	// if (inputstartswith(inpt, "echo -n "))
	// 	ft_printf("%s", inpt + 5);
	// else
	// 	ft_printf("%s\n", inpt + 5);
	// *(shell_info->status) = 0;
	//OPTION 1. END

	// //OPTION 2. WHEN THE STRING AFTER 'cd ' IS PASSED
	if (inputstartswith(inpt, "echo -n "))
		ft_printf("%s", inpt);
	else
		ft_printf("%s\n", inpt);
	*(shell_info->status) = 0;
	// //OPTION 2. END


	// char	**output;
	// char	*str;

	// output = ft_split(inpt + 5, ' ');
	// // str = *output;
	// // while (str)
	// // {
	// // 	str = backslash_piece(str);
	// // 	str++;
	// // }
	// while (*output)
	// {
	// ft_printf("op %s\n",*output);
	// // ft_printf("bs %s\n",backslash_piece(*output));
	// 	// *output = backslash_piece(*output);
	// 	output++;
	// }
	// str = *output;
	// while (str)
	// {
	// 	ft_printf("%s", str);
	// 	str++;
	// }
	// ft_printf("bs %s\n",backslash(inpt));
	// ft_printf('\\');
}



//ECHO WITH OPTION N!