/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:46 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/29 13:41:54 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// git push origin thalia_branch 

void	leaks(void)
{
	system("leaks minishell");
}
// int	main(void)
int	main(int argc, char **argv, char **env)
{
	char	*prompt;
	char	*prompt_with_dollar;
	t_shell	*shell_info;

	atexit(&leaks);
	(void)argv;
	if (argc != 1)
		ft_printf("Minishell executable does not use arguments\n");
	shell_info = ft_calloc(1, sizeof(t_shell));
	shell_info->first_token_node = ft_calloc(1, sizeof(t_token));
	prompt = ft_strjoin("minishell ", getenv("USER"));
	if (!prompt)
		return (0);
	prompt_with_dollar = ft_strjoin(prompt, "$ ");
	if (!prompt_with_dollar)
		return (free(prompt), 0);
	catchsignal();
	initialise_basics(argc, env, shell_info);
	inpt_handler(prompt_with_dollar, argv, env, shell_info);
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
	getcwd(cwd, sizeof(cwd));
	ft_printf("cwd: %s\n", cwd);
	shell_info->cwd = ft_strdup(cwd); // ft_strdup since cwd is local variable, and it dealloc when fn is finished.
	ft_printf("info->cwd: %s\n", shell_info->cwd);

}
