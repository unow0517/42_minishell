/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:46 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/26 16:31:30 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// git push origin thalia_branch 
void	inpt_handler(char *prompt, char **argv, char **env, t_shell *info)
{
	char	*inpt;
	char	*full_path;
	t_token	*token;
	char 	*cmd;
	
	// (void)full_path;
	// (void)argv;
	// (void)env;
	// t_mini	*shell_info;

	// shell_info = malloc(sizeof(t_mini));
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
		if (!inputis(inpt, ""))
			add_history(inpt);
		if (*inpt == ' ')
			inpt = rm_starting_ws(inpt);
		multiple_ws_to_single(inpt);

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
			full_path = find_cmd_in_env(cmd, env);
			ft_printf("full_path: %s\n", full_path);
			if (fork() == 0)
			{
				printf("\ninput: %s\n\n", inpt);
				execute(full_path, inpt, env);
				perror("execve");
				exit(EXIT_FAILURE);
				
			}
			else
			{
				wait(NULL);
				ft_printf("child process finished\n");
			}
		}
		else
			ft_printf("minishell: %s: command not found\n", inpt);




		if (inpt)
			free(inpt);
		
	}

}

// void	free_small_linked(t_shell shell_info)
// {
	
// }

// int	main(void)
int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	*prompt_with_dollar;
	t_shell	*shell_info;
	// t_shell	*info;
	// char	cwd[1024];

	(void)argv;
	if (argc != 1)
		ft_printf("Minishell executable does not use arguments\n");
	shell_info = ft_calloc(sizeof(t_shell), 1);
	shell_info->first_token_node = ft_calloc(sizeof(t_token), 1);
	prompt = ft_strjoin("minishell ", getenv("USER"));
	if (!prompt)
		return (0);
	prompt_with_dollar = ft_strjoin(prompt, "$ ");
	if (!prompt_with_dollar)
		return (free(prompt), 0);
	catchsignal();
	// shell_info = malloc(sizeof(t_mini));
	// shell_info->cwd = getcwd(cwd, sizeof(cwd));
	initialise_basics(argc, env, shell_info);
	// inpt_handler(prompt_with_dollar, argv, env, shell_info, info);
	inpt_handler(prompt_with_dollar, argv, env, shell_info);
	// (void)argv;
	// (void)env;
	if (shell_info)
		free(shell_info);
	if (prompt)
		free(prompt);
	if (prompt_with_dollar)
		free(prompt_with_dollar);
	return (0);
}

void	initialise_basics(int argc, char **env, t_shell *shell_info)
{
	char	cwd[1024];
	shell_info->argc = argc;
	shell_info->env = env; //env not properly initialized?
	shell_info->cwd = getcwd(cwd, sizeof(cwd));
}

