/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:46 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/26 12:44:34 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle input from user.
void	inpt_handler(char *prompt, char **argv, char **env, t_mini *shell_info)
{
	char	*inpt;
	char	*full_path;

	while (1)
	{
		signal(SIGINT, sighandler);
		if (prompt)
			inpt = readline(prompt);
		if (!inpt) //ctrl+D go through here
		{
			free(shell_info);
			system("leaks minishell | grep leaked");
			// system("leaks minishell");
			exit(0) ;
		}
		if (inputis(inpt, "exit")) //these both if statements in same, then seg fault for ctrl+d
		{
			free(shell_info);
			system("leaks minishell | grep leaked");
			// system("leaks minishell");
			exit(0) ;
		}
		if (!inputis(inpt, "")) //if input is not empty, put in history
			add_history(inpt);
		if (*inpt == ' ') //removing starting whitespaces
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
		else if (find_cmd_in_env(inpt, env)) // search user input cmd looping PATH in env, if exists run in child process
		{
			full_path = find_cmd_in_env(inpt, env); //take cmd, and find a correct full path from PATH in env.
			if (fork() == 0) //make child process and run the cmd
			{
				execute(full_path, inpt, env);
				perror("execve");
			}
			else
			{
				wait(NULL);
				ft_printf("child process finished\n");
			}
		}
		else 
			ft_printf("minishell: %s: command not found\n", inpt); //when no cmd is 
		if (inpt)
			free(inpt);
	}

}

//minishell struct malloc, free the struct and prompt
int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	*prompt_with_dollar;
	t_mini	*shell_info;
	char	cwd[1024];

	prompt = ft_strjoin("minishell ", getenv("USER"));
	prompt_with_dollar = ft_strjoin(prompt, "$ ");
	catchsignal();
	(void)argc;
	shell_info = malloc(sizeof(t_mini));
	shell_info->cwd = getcwd(cwd, sizeof(cwd));
	inpt_handler(prompt_with_dollar, argv, env, shell_info);
	if (shell_info)
		free(shell_info);
	if (prompt)
		free(prompt);
	if (prompt_with_dollar)
		free(prompt_with_dollar);
	return (0);
}
