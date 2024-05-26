/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:36:23 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/26 19:45:32 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_split_thalia(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// void	handle_error(char *str)
// {
// 	perror(str);
// 	exit(EXIT_FAILURE);
// }
