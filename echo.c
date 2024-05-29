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

static void	echo_without_flag(char **split_arg)
{
	int		i;
	int		j;
	int		sq;
	int		dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (split_arg && split_arg[i])
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
	while (split_arg && split_arg[i])
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

int	is_flag(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp("-n", str, 2) == 0 && ft_strlen(str) == 2)
		i = 1;
	else if (ft_strncmp("'-n'", str, 4) == 0 && ft_strlen(str) == 4)
		i = 1;
	else if (ft_strncmp("\"-n\"", str, 4) == 0 && ft_strlen(str) == 4)
		i = 1;
	return (i);
}

void	run_echo(char *inpt, t_shell *shell_info)
{
	char	**split_arg;

	if (inpt)
	{
		split_arg = split_ms(inpt, ' ');
		if (split_arg)
		{
			if (is_flag(split_arg[0]))
				echo_with_flag(split_arg);
			else
				echo_without_flag(split_arg);
		}
		if (split_arg)
			free_split_thalia(split_arg);
	}
	else
		write (1, "\n", 1);
	if (num_of_total_cmds(shell_info->first_command) > 1)
		exit(0);
	*(shell_info->status) = 0;
}
