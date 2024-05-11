/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:46 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/09 13:54:40 by yowoo            ###   ########.fr       */
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
ft_printf("minishell______DONE_________________\n");
	return (0);
}
//FREE ENV_MINI REQUIRED BY EXIT!

//env char ** to linkedlist, necessary for builtins export, unset.
t_env_mini	*env_to_envmini(char	**env, t_env_mini *env_mini)
{
	char		*name;
	char		*value;
	t_env_mini	*ptr;
	char		**ft_splitted;

	ptr = env_mini;
	while (env && *env)
	{
		ft_splitted = ft_split(*env, '=');
		name = ft_splitted[0];
		value = ft_splitted[1];
		env_mini->name = name;
		env_mini->value = value;
		env++;
		if (env && *env)
		{
			env_mini->next = malloc(sizeof(t_env_mini));
			env_mini = env_mini->next;
		}
	}
	return (ptr);
}
void	initialise_basics(int argc, char **argv, char **env, t_shell *shell_info)
{
	shell_info->argc = argc;
	shell_info->argv = argv;
	shell_info->env = env;
	shell_info->env_mini = malloc(sizeof(t_env_mini));
	shell_info->env_mini = env_to_envmini(env, shell_info->env_mini);
	getcwd(shell_info->cwd, sizeof(shell_info->cwd));
	shell_info->tokens = NULL;
	shell_info->user_input = NULL;
	shell_info->first_command = NULL;
	// shell_info->cwd = ft_strdup(shell_info->cwd); // ft_strdup since cwd is local variable, and it dealloc when fn is finished.
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