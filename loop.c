/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:12:21 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/07 18:59:47 by tsimitop         ###   ########.fr       */
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
		if (num_of_total_cmds(shell_info->first_command) > 1) // create pipes before redirections, if I have a redir I should use this and over-write the pipe(fd)
			init_pipe(shell_info, cur);
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
		if (cur->fd[0] != -1)
			close(cur->fd[0]);
		if (cur->fd[1] != -1)
			close(cur->fd[1]);
		waitpid(pid, status, 0);
	}
}

void	init_pipe(t_shell *shell_info, t_command *cur)
{
	t_command	*last_cmd;
	t_command	*first_cmd;

	first_cmd = shell_info->first_command;
	last_cmd = get_last_cmd(first_cmd);
	if (pipe(cur->fd) == -1)
	{
		perror("pipe failed"); //fix proper message and exit
		exit(1);
	}
	if (cur == first_cmd)
	{
		close(cur->fd[0]);
		dup2(cur->fd[1], STDOUT_FILENO); //add checks for dup2?
		// close(cur->fd[1]);
	}
	else if (cur == last_cmd)
	{
		close(cur->fd[1]);
		dup2(cur->fd[0], STDIN_FILENO);
		// close(cur->fd[0]);
	}
	else // i need both ends of the pipe if my command is in between pipes else I have separate for first and last commands
	{
		dup2(cur->fd[0], STDIN_FILENO);
		dup2(cur->fd[1], STDOUT_FILENO);
		// close(cur->fd[0]);
		// close(cur->fd[1]);
	}
}

t_command	*get_last_cmd(t_command *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	handle_redir(t_command *cur)
{
	if (cur->input_fd != -1)
	{
		if (dup2(cur->input_fd, STDIN_FILENO) == -1) //cur->standard_input from initialise_cmd_node
		{
			perror("dup2 for input_fd failed");
			exit(EXIT_FAILURE);
		}
		close(cur->input_fd);
	}
	if (cur->output_fd != -1)
	{
		if (dup2(cur->output_fd, STDOUT_FILENO) == -1) //cur->standard_output from initialise_cmd_node
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

int	num_of_total_cmds(t_command *cur)
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
