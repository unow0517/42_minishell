/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:18:23 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/19 18:19:32 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pwd asdf => pwd should work 
void	printpwd(t_mini *shell_info)
{
	char			cwd[1024];

	if (!shell_info->cwd)
	{
		shell_info->cwd = getcwd(cwd, sizeof(cwd));
		if (!shell_info->cwd)
			ft_printf("Error saving cwd in shell_info struct");
	}
	ft_printf("%s\n", shell_info->cwd);


}
