/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:12:21 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/09 20:17:21 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inpt_handler(char **argv, char **env, t_shell *shell_info)
{
	int			status;
	// t_command	*cur;

	shell_info->user_input = NULL;
	while (1)
	{
		signal(SIGINT, sighandler);
		shell_info->user_input = readline(shell_info->prompt);
		parse_input(shell_info);
		print_token_types(shell_info);
		// cur = shell_info->first_command;
		// if (num_of_total_cmds(shell_info->first_command) > 1) // create pipes before redirections, if I have a redir I should over-write the pipe(fd) with the file fd
		// 	init_pipe(shell_info, cur);
		// while (cur)
		// {
		// 	printf("exec loop\n");
		// 	executor(shell_info, &status, cur);
		// 	cur = cur->next;
		// }
		execution_cases(shell_info, &status);
		if (!shell_info->user_input)
		{
			// free(shell_info);
			exit(0) ;
		}
		if (inputis(shell_info->user_input, "exit")) //these both if statements in same, then seg fault for ctrl+d
		{
			// free(shell_info);
			exit(0) ;
		}
		if (!inputis(shell_info->user_input, ""))
			add_history(shell_info->user_input);
		if (*shell_info->user_input == ' ')
			shell_info->user_input = rm_starting_ws(shell_info->user_input);
		multiple_ws_to_single(shell_info->user_input);
		//have to run this after split cmd by space.
write(2, "___________________________DEBUG___________________________\n", ft_strlen("___________________________DEBUG___________________________\n"));
		if (inputis(shell_info->user_input, ""))
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else if (inputstartswith(shell_info->user_input, "echo "))
			run_echo(shell_info->user_input);
		else if (inputstartswith(shell_info->user_input, "cd "))
			run_cd(shell_info->user_input, shell_info);
		else if (inputstartswith(shell_info->user_input, "pwd ") | inputis(shell_info->user_input, "pwd"))
		{
			printpwd(shell_info);
		}
		else if (inputis(shell_info->user_input, "env") | inputis(shell_info->user_input, "env "))
			run_env(shell_info->user_input, env);
		else if (inputstartswith(shell_info->user_input, "history"))
			print_history(shell_info->user_input);
		(void)argv;
		// else if (inputhas(shell_info->user_input, '|'))
		// 	run_pipe(shell_info->user_input, argv, env); // not perfect
	free_tokens(&shell_info->tokens);
	free_cmd_list(&shell_info->first_command);
	}
}
