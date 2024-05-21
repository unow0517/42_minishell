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

void	run_echo(char *inpt)
{
	if (inputstartswith(inpt, "echo -n "))
		ft_printf("%s", inpt + 5);
	else
		ft_printf("%s\n", inpt);
}

// void	run_echo(t_command *cmd, char *inpt)
// {
// 	char *str;

// 	str = inpt;
// 	if (cmd->output_fd != -1)
// 		write(cmd->output_fd, "%s\n", ft_strlen(inpt));
// 	else
// 		write(cmd->output_fd, "%s\n", ft_strlen(inpt));
// }