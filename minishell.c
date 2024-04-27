/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:46 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/27 20:51:26 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// git push origin thalia_branch 


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
	inpt_handler(prompt_with_dollar, argv, env, shell_info, argc);
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

