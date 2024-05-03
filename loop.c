/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:12:21 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/03 18:28:33 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inpt_handler(char **argv, char **env, t_shell *shell_info)
{
	// char	*full_path;
	char	*cmd;
	int		status;
	// pid_t	pid;

		// if (!shell_info)
		// 	shell_info = ft_calloc(1, sizeof(t_shell));
	shell_info->user_input = NULL;
	while (1)
	{
		signal(SIGINT, sighandler);
		shell_info->user_input = readline(shell_info->prompt);
		parse_input(shell_info);
		(void)status;
		executor(shell_info);
		// create_tokens(shell_info);
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
// ft_printf("loop shell_info->user_input = %s\n", shell_info->user_input);
		cmd = get_first_word(shell_info->user_input);
		if (!cmd)
		{
			perror("cmd not allocated");
			exit(1);
		}
		if (inputis(shell_info->user_input, ""))
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else if (inputhas(shell_info->user_input, '|'))
			run_pipe(shell_info->user_input, argv, env); // not perfect
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
		else
			ft_printf("minishell: %s: command not found\n", shell_info->user_input);
		// else if (find_cmd_in_env(cmd, env))
		// {
		// 	pid = fork();
		// 	if (pid == 0)
		// 	{
		// 		full_path = find_cmd_in_env(cmd, env);
		// 		// ft_printf("full_path: %s\n", full_path);
		// 		// printf("\ninput: %s\n\n", shell_info->user_input);
		// 		execve(full_path, ft_split(shell_info->user_input, ' '), env);
		// 		perror("execve");
		// 		exit(EXIT_FAILURE);
		// 	}
		// 	else
		// 	{
		// 		waitpid(pid, &status, 0);
		// 		ft_printf("child process finished\n");
		// 	}
		// }
		// shell_info->user_input = NULL;
	free_tokens(&shell_info->tokens);
	}

}

void	executor(t_shell *shell_info)
{
	t_command	*cmd_node;
	pid_t		pid;
	char		*full_path;

	cmd_node = shell_info->first_command;
	while (cmd_node)
	{
		pid = fork();
		if (pid == 0)
		{
			printf("cmd_node->cmd = %s\n", cmd_node->cmd);
			printf("heyyyy\n");
			full_path = find_cmd_in_env(cmd_node->cmd, shell_info->env);
			execve(full_path, cmd_node->full_cmd, shell_info->env);
			perror("execve");
			// execve(full_path, ft_split(shell_info->user_input, ' '), env);
		}
		cmd_node = cmd_node->next;
	}
}
