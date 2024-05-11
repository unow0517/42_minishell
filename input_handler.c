/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:12:21 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/10 14:24:39 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inpt_handler(char **argv, char **env, t_shell *shell_info)
{
	int			status;
	t_command	*cur;
	char		*usr_inpt;

	shell_info->user_input = NULL;
	while (1)
	{
		signal(SIGINT, sighandler);
		shell_info->user_input = readline(shell_info->prompt);
		parse_input(shell_info); //create, parse tokens
		print_token_types(shell_info);
		cur = shell_info->first_command;
		usr_inpt = shell_info->user_input;
		if (!usr_inpt)
		{
			// free(shell_info);
			exit(0) ;
		};
		if (inputis(usr_inpt, "exit")) //if these 'if statements' in one statement, then seg fault for ctrl+d
		{
			// free(shell_info);
			exit(0) ;
		};
		dollar_expand(shell_info);
		if (!inputis(usr_inpt, ""))
			add_history(usr_inpt);
		if (*usr_inpt == ' ')
			usr_inpt = rm_starting_ws(usr_inpt);
		multiple_ws_to_single(usr_inpt);
		//have to run this after split cmd by space.;
		if (inputis(usr_inpt, ""))
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else if (inputhas(usr_inpt, '|'))
			run_pipe(usr_inpt, argv, env); // not perfect;
		else if (inputstartswith(usr_inpt, "echo "))
			run_echo(usr_inpt);
		else if (inputstartswith(usr_inpt, "cd "))
			run_cd(usr_inpt, shell_info);
		else if (inputstartswith(usr_inpt, "pwd ") | inputis(usr_inpt, "pwd"))
		{
			printpwd(shell_info);
		}
		else if(inputstartswith(usr_inpt, "env ") | inputis(usr_inpt, "env"))
			run_env(shell_info);
		else if(inputstartswith(usr_inpt, "export ") | inputis(usr_inpt, "export"))
			run_export(shell_info);
		else if(inputstartswith(usr_inpt, "unset ") | inputis(usr_inpt, "unset"))
			run_unset(shell_info);
		else if (inputstartswith(usr_inpt, "history"))
			print_history(usr_inpt);
		else if (find_cmd_in_env(cur->cmd, env))
		{
			while (cur)
			{
				executor(shell_info, &status, cur);
				cur = cur->next;
			}
		}
		else
			ft_printf("minishell: %s: command not found\n", usr_inpt); //No command not found error!
	free_tokens(&shell_info->tokens);
	free_cmd_list(&shell_info->first_command);
	}
}
