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

void	inpt_handler(char **argv, t_shell *shell_info)
{
	int			status;

	status = 0;
	shell_info->user_input = NULL;
	while (1)
	{
		signal(SIGINT, sighandler);
		shell_info->user_input = readline(shell_info->prompt);
		// ft_printf("bs %s\n",backslash_piece(shell_info->user_input));
    	
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
    	// shell_info->user_input = expand(shell_info);
		expand(shell_info);
		// ft_printf("outputinhandler %s\n", shell_info->user_input);
		parse_input(shell_info, &status);
// printf("exit status = %i\n", status); //if echo $? set status to NULL at the end of the builtin
		// execution_cases(shell_info, &status);
    // if (ft_strlen(dollar_expand(shell_info)) != 0)
    //   shell_info->user_input = dollar_expand(shell_info);
		if (*shell_info->user_input == ' ')
			shell_info->user_input = rm_starting_ws(shell_info->user_input);
		multiple_ws_to_single(shell_info->user_input);

		//have to run this after split cmd by space.
		if (inputis(shell_info->user_input, ""))
		{
			rl_on_new_line();
			rl_redisplay();
		}
    
		if (inputstartswith(shell_info->user_input, "echo "))
			run_echo(shell_info->user_input);
		else if (inputstartswith(shell_info->user_input, "cd "))
    {
			run_cd(shell_info->user_input, shell_info);
      // ft_printf("chdir %d\n", chdir(shell_info->user_input + 3));
    }
		else if (inputstartswith(shell_info->user_input, "pwd ") | inputis(shell_info->user_input, "pwd"))
			run_pwd(shell_info);
		else if (inputis(shell_info->user_input, "env ") | inputis(shell_info->user_input, "env"))
			run_env(shell_info);
		else if (inputstartswith(shell_info->user_input, "export ") | inputis(shell_info->user_input, "export"))
			run_export(shell_info);
    	else if (inputstartswith(shell_info->user_input, "unset ") | inputis(shell_info->user_input, "unset"))
			run_unset(shell_info);
		else if (inputstartswith(shell_info->user_input, "history"))
			print_history(shell_info->user_input);
    	else if (!inputis(shell_info->user_input, ""))
			ft_printf("minishell: %s: command not found\n", shell_info->user_input); //No command not found error if this line doesnt exist!


    //OLDPWD implement
		(void)argv;
	free_tokens(&shell_info->tokens);
	free_cmd_list(&shell_info->first_command);
	// printf("shell_info->syntax_error = %i\n", shell_info->syntax_error);
	shell_info->syntax_error = false;
	}
}