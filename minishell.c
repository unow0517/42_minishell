/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:46 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/13 14:58:05 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	shell_info;

	if (argc != 1)
		printf("Minishell executable does not use arguments\n");
	initialise_basics(argv, env, &shell_info);
	if (create_prompt(&shell_info) != 0)
		return (EXIT_FAILURE);
	catchsignal();
	inpt_handler(&shell_info);
	return (0);
}

void	init_env_mini(t_env_mini *env_mini)
{
	env_mini->name = NULL;
	env_mini->value = NULL;
	env_mini->next = NULL;
}

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
		if (env && *env && !inputis(name, "OLDPWD"))
		{
			env_mini->next = malloc(sizeof(t_env_mini));
			env_mini->next->name = NULL;
			env_mini->next->value = NULL;
			env_mini = env_mini->next;
		}
	}
	return (ptr);
}

void	initialise_basics(char **argv, char **env, t_shell *shell_info)
{
	shell_info->argv = argv;
	shell_info->env = env;
	shell_info->env_mini = malloc(sizeof(t_env_mini));
	init_env_mini(shell_info->env_mini);
	shell_info->env_mini = env_to_envmini(env, shell_info->env_mini);
	getcwd(shell_info->cwd, sizeof(shell_info->cwd));
	shell_info->tokens = NULL;
	shell_info->user_input = NULL;
	shell_info->first_command = NULL;
	shell_info->fd[0] = -1;
	shell_info->fd[1] = -1;
	shell_info->syntax_error = false;
	shell_info->status = ft_calloc(1, sizeof(int));
	*shell_info->status = 0;
	shell_info->isheredoc = 0;
}

int	create_prompt(t_shell *shell_info)
{
	char	*prompt;
	char	*prompt_with_dollar;

	prompt = NULL;
	prompt = ft_strjoin("minishell__", getenv("USER"));
	if (!prompt)
		return (1);
	prompt_with_dollar = ft_strjoin(prompt, "$ ");
	if (!prompt_with_dollar)
		return (free(prompt), 1);
	ft_memset(shell_info->prompt, 0, 2048);
	ft_strlcat(shell_info->prompt, prompt_with_dollar, 2048);
	free(prompt);
	free(prompt_with_dollar);
	return (0);
}
