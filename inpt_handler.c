/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inpt_handler.c                                     :+:      :+:    :+:   */
/*   inpt_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:12:21 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/13 15:14:32 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inpt_handler(t_shell *shell_info)
{
	shell_info->user_input = NULL;
	while (1)
	{
		signal(SIGINT, sighandler);
		shell_info->user_input = readline(shell_info->prompt);
		if (shell_info->user_input && !inputis(shell_info->user_input, ""))
			add_history(shell_info->user_input);
		ft_expand(shell_info);
		parse_input(shell_info);
		execution_cases(shell_info);
		if (!shell_info->user_input || inputis(shell_info->user_input, "exit"))
		{
			write(1, "\n", 1);
			free_cmd_list(&shell_info->first_command);
			free_tokens(&shell_info->tokens);
			free_shell(shell_info);
			// free_envmini(shell_info->env_mini);
			system("leaks minishell");
			exit(0);
		}
		reset(shell_info);
		free(shell_info->user_input);
	}
}
