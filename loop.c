/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:12:21 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/07 16:29:46 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inpt_handler(char **argv, char **env, t_shell *shell_info)
{
	char	*cmd;
	int		status;
	t_command	*cur;
	shell_info->user_input = NULL;
	while (1)
	{
		signal(SIGINT, sighandler);
		shell_info->user_input = readline(shell_info->prompt);
		parse_input(shell_info);
		print_token_types(shell_info);
		cur = shell_info->first_command;
		while (cur)
		{
			executor(shell_info, &status, cur);
			cur = cur->next;
		}
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
	free_tokens(&shell_info->tokens);
	free_cmd_list(&shell_info->first_command);
	}
}

void	executor(t_shell *shell_info, int *status, t_command *cur)
{
	pid_t		pid;
	char		*full_path;

	pid = fork();
	if (pid == 0)
	{
		// if (num_of_remaining_cmds(cur) > 1)
		// 	init_pipe(cur);
		handle_redir(cur);
		full_path = find_cmd_in_env(cur->cmd, shell_info->env);
		// print_split(cur->full_cmd);
		execve(full_path, cur->full_cmd, shell_info->env);
		printf("passed execve\n");
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (cur->input_fd != -1)
			close(cur->input_fd);
		if (cur->output_fd != -1)
			close(cur->output_fd);
		waitpid(pid, status, 0);
	}
}

void	init_pipe(t_command *cur)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe failed"); //fix proper message and exit
		exit(1);
	}
	if (cur->input_fd != -1)
		dup2(fd[0], STDIN_FILENO);
	if (cur->output_fd != -1)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

void	handle_redir(t_command *cur)
{
	if (cur->input_fd != -1)
	{
		if (dup2(cur->input_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 for input_fd failed");
			exit(EXIT_FAILURE);
		}
		close(cur->input_fd);
	}
	if (cur->output_fd != -1)
	{
		if (dup2(cur->output_fd, STDOUT_FILENO) == -1)
		{
			perror("dup2 for output_fd failed");
			exit(EXIT_FAILURE);
		}
		close(cur->output_fd);
	}
}

int	num_of_remaining_cmds(t_command *cur)
{
	int	counter;

	counter = 0;
	while (cur)
	{
		cur = cur->next;
		counter++;
	}
	return (counter);
}
