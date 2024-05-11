/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:46 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/11 20:25:00 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// git push origin thalia_branch 

// void	leaks(void)
// {
// 	system("leaks minishell");
// }

int	main(int argc, char **argv, char **env)
{
	t_shell	shell_info;

	// atexit(&leaks);
	if (argc != 1)
		ft_printf("Minishell executable does not use arguments\n");
	initialise_basics(argc, argv, env, &shell_info);
	if (create_prompt(&shell_info) != 0)
		return (EXIT_FAILURE);
	catchsignal();
	inpt_handler(argv, env, &shell_info);
	return (0);
}

void	initialise_basics(int argc, char **argv, char **env, t_shell *shell_info)
{
	shell_info->argc = argc;
	shell_info->argv = argv;
	shell_info->env = env;
	getcwd(shell_info->cwd, sizeof(shell_info->cwd));
	shell_info->tokens = NULL;
	shell_info->user_input = NULL;
	shell_info->first_command = NULL;
	shell_info->fd[0] = -1;
	shell_info->fd[1] = -1;
}

int	create_prompt(t_shell *shell_info)
{
	char	*prompt;
	char	*prompt_with_dollar;

	prompt = NULL;
	prompt = ft_strjoin("\033[0;35mminishell\033[0m ", getenv("USER"));
	if (!prompt)
		return (1);
	prompt_with_dollar = ft_strjoin(prompt, "$ ");
	if (!prompt_with_dollar)
		return (free(prompt), 1);
	ft_memset(shell_info->prompt, 0, 1024);
	ft_strlcat(shell_info->prompt, prompt_with_dollar, 1024);
	free(prompt);
	free(prompt_with_dollar);
	return (0);
}