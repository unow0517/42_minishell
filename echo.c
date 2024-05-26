/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 17:49:45 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/26 17:49:45 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echo_without_flag(char **split_arg);
static void	echo_with_flag(char **split_arg);

void	run_echo(char *inpt, t_shell *shell_info)
{
	char	**split_arg;

	split_arg = split_ms(inpt, ' ');
	if (ft_strncmp("-n", split_arg[0], 2) == 0 && strlen(split_arg[0]) == 2)
		echo_with_flag(split_arg);
	else
		echo_without_flag(split_arg);
	*(shell_info->status) = 0;
}

static void	echo_without_flag(char **split_arg)
{
	int		i;
	int		j;
	int		sq;
	int		dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (split_arg &&split_arg[i])
	{
		j = 0;
		if (i != 0)
			write (1, " ", 1);
		while (split_arg[i][j])
		{
			if ((split_arg[i][j] == '\'' && dq == 0) || \
			(split_arg[i][j] == '"' && sq == 0))
				update_quote_state_str(split_arg[i], &sq, &dq, j);
			else
				write (1, &(split_arg[i][j]), 1);
			j++;
		}
		i++;
	}
	write (1, "\n", 1);
}

static void	echo_with_flag(char **split_arg)
{
	int		i;
	int		j;
	int		sq;
	int		dq;

	i = 1;
	sq = 0;
	dq = 0;
	while (split_arg &&split_arg[i])
	{
		j = 0;
		if (i != 1)
			write (1, " ", 1);
		while (split_arg[i][j])
		{
			if ((split_arg[i][j] == '\'' && dq == 0) || \
			(split_arg[i][j] == '"' && sq == 0))
				update_quote_state_str(split_arg[i], &sq, &dq, j);
			else
				write (1, &(split_arg[i][j]), 1);
			j++;
		}
		i++;
	}
}