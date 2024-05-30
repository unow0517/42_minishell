/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:08:36 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/30 17:23:55 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_whitespace(char *inpt, int i)
{
	while (inpt[i] != '\0' && \
	(inpt[i] == ' ' || inpt[i] == '\t' || inpt[i] == '\r' || \
	inpt[i] == '\n' || inpt[i] == '\v' || inpt[i] == '\f'))
		i++;
	return (i);
}

void	nullify_ints_four(int *inside_sq, int *inside_dq, int *i, int *counter)
{
	*i = 0;
	*counter = 0;
	*inside_dq = 0;
	*inside_sq = 0;
}

//1ST WORD OF STRING, WHICH IS NOT METACHAR.
char	*get_first_word(char *argv)
{
	int		i;
	char	*small_cmd;

	i = 0;
	while (argv[i] != '\0' && argv[i] != ' ' && argv[i] != '>' && \
	argv[i] != '<' && argv[i] != '|' && argv[i] != '"' && argv[i] != '\'')
		i++;
	small_cmd = ft_calloc(i + 1, sizeof(char));
	if (!small_cmd)
		return (NULL);
	i = 0;
	while (argv[i] != '\0' && argv[i] != ' ' && argv[i] != '>' && \
	argv[i] != '<' && argv[i] != '|' && argv[i] != '"' && argv[i] != '\'')
	{
		small_cmd[i] = argv[i];
		i++;
	}
	return (small_cmd);
}

void	proc_exit(int status, t_shell *shell_info)
{
	if (num_of_total_cmds(shell_info->first_command) > 1)
		exit(status);
	*(shell_info->status) = status;
}
