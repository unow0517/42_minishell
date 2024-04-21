/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:46 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/21 01:28:41 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inpt_handler(char *prompt, char **argv, char **env, t_mini *shell_info)
{
	char	*inpt;
	char	*full_path;
	// t_mini	*shell_info;

	// shell_info = malloc(sizeof(t_mini));
	while (1)
	{
		signal(SIGINT, sighandler);
		if (prompt)
			inpt = readline(prompt);
		if (!inpt)
		{
			free(shell_info);
			system("leaks minishell | grep leaked");
			exit(0) ;
		}
		if (inputis(inpt, "exit")) //these both if statements in same, then seg fault for ctrl+d
		{
			free(shell_info);
			system("leaks minishell | grep leaked");
			exit(0) ;
		}
		if (!inputis(inpt, ""))
			add_history(inpt);
		if (*inpt == ' ')
			inpt = rm_starting_ws(inpt);
		multiple_ws_to_single(inpt);

		//have to run this after split cmd by space.
		if (inputis(inpt, ""))
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else if (inputhas(inpt, '|'))
			run_pipe(inpt, argv, env); // not perfect
		else if (inputstartswith(inpt, "echo "))
			run_echo(inpt);
		else if (inputstartswith(inpt, "cd "))
			run_cd(inpt, shell_info);
		else if (inputstartswith(inpt, "pwd ") | inputis(inpt, "pwd"))
			printpwd(shell_info);
		else if (inputis(inpt, "env") | inputis(inpt, "env "))
			run_env(inpt, env);
		else if (inputstartswith(inpt, "history"))
			print_history(inpt);
		else if (find_cmd_in_env(inpt, env))
		{
			full_path = find_cmd_in_env(inpt, env);
			execute(full_path, inpt, env);
		}
		else
			ft_printf("minishell: %s: command not found\n", inpt);
		free(inpt);
	}
	free(shell_info);
}

// int	main(void)
int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	*prompt_with_dollar;
	t_mini	*shell_info;
	char	cwd[1024];


	prompt = ft_strjoin("minishell ", getenv("USER"));
	prompt_with_dollar = ft_strjoin(prompt, "$ ");
	catchsignal();
	// inpt_handler(prompt_with_dollar);
	(void)argc;
	shell_info = malloc(sizeof(t_mini));
	// shell_info->cwd = "";
	shell_info->cwd = getcwd(cwd, sizeof(cwd));
	inpt_handler(prompt_with_dollar, argv, env, shell_info);
	if (prompt)
		free(prompt);
	if (prompt_with_dollar)
		free(prompt_with_dollar);
	return (0);
}
