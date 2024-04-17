/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:46 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/17 15:31:37 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*starting_ws(char *string)
{
	char	*ptr;
	char	*string_0;

	string_0 = string;
	string++;
	while (*string != '\0')
	{
		if (*string == ' ')
			string++;
		else
			break ;
	}
	ptr = ft_strdup(string);
	free(string_0);
	return (ptr);
}

void	inpt_handler(char *prompt)
{
	char			*inpt;

	while (1)
	{
		signal(SIGINT, sighandler);
		inpt = readline(prompt);
		if (!inpt | inputis(inpt, "exit"))
		{
			system("leaks minishell | grep leaked");
			break ;
		}
		if (!inputis(inpt, ""))
			add_history(inpt);
		if (*inpt == ' ')
			inpt = starting_ws(inpt);
		if (inputis(inpt, ""))
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else if (inputis(inpt, "pwd"))
			printpwd();
		else if (inputstartswith(inpt, "history"))
			print_history(inpt);
		else
			ft_printf("minishell: %s: command not found\n", inpt);
		free(inpt);
	}
}

int	main(void)
{
	char			*prompt;
	char			*prompt_with_dollar;

	prompt = ft_strjoin("minishell ", getenv("USER"));
	prompt_with_dollar = ft_strjoin(prompt, "$ ");
	catchsignal();
	inpt_handler(prompt_with_dollar);
	if (prompt)
		free(prompt);
	if (prompt_with_dollar)
		free(prompt_with_dollar);
	return (0);
}
