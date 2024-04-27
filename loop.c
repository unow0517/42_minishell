/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:12:21 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/27 21:00:36 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inpt_handler(char *prompt, char **argv, char **env, t_shell *info, int argc)
{
	char	*inpt;
	char	*full_path;
	t_token	*token;
	char 	*cmd;
	int		status;
	pid_t	pid;
	
	// (void)full_path;
	// (void)argv;
	// (void)env;
	// t_mini	*shell_info;
	// shell_info = malloc(sizeof(t_mini));
	inpt = NULL;
	while (1)
	{
		signal(SIGINT, sighandler);
		if (prompt)
		{
			inpt = readline(prompt);
			// ft_printf("INPUT: %s\n", inpt);
		}
		if (!inpt)
		{
			// free(shell_info);
			free(info);
			system("leaks minishell | grep leaked");
			// system("leaks minishell");
			exit(0) ;
		}
		if (inputis(inpt, "exit")) //these both if statements in same, then seg fault for ctrl+d
		{
			// free(shell_info);
			free(info);
			system("leaks minishell | grep leaked");
			// system("leaks minishell");
			exit(0) ;
		}
// ft_printf("_________________________________________\n");
		if (!inputis(inpt, ""))
			add_history(inpt);
		if (*inpt == ' ')
			inpt = rm_starting_ws(inpt);
		multiple_ws_to_single(inpt);
		if (!info)
			info = ft_calloc(sizeof(t_shell), 1);
		if (!*(info->first_token_node))
			info->first_token_node = ft_calloc(sizeof(t_token), 1);
		(void)argc;
		// initialise_basics(argc, env, info);
		//have to run this after split cmd by space.
		token = *(info->first_token_node);
		input_types(inpt, info, token);
		cmd = get_directory_name(inpt);//ls simple
		// ft_printf("cmd = %s\n", cmd);
		if (!cmd)
		{
			perror("cmd not allocated");
			exit(1);
		}

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
			run_cd(inpt, info);
		else if (inputstartswith(inpt, "pwd ") | inputis(inpt, "pwd"))
			printpwd(info);
		else if (inputis(inpt, "env") | inputis(inpt, "env "))
			run_env(inpt, env);
		else if (inputstartswith(inpt, "history"))
			print_history(inpt);
		else if (find_cmd_in_env(cmd, env))
		{
			pid = fork();
			if (pid == 0)
			{
				full_path = find_cmd_in_env(cmd, env);
				ft_printf("full_path: %s\n", full_path);
				printf("\ninput: %s\n\n", inpt);
				// printf("\nenv[2]: %s\n\n", env[2]);
				execute(full_path, inpt, env);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, &status, 0);
				ft_printf("child process finished\n");
			}
		}
		else
			ft_printf("minishell: %s: command not found\n", inpt);

		// free_small_linked(info);
		if (inpt)
			free(inpt);
		
	}

}