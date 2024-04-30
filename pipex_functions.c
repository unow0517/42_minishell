/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:36:23 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/30 14:30:31 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_first_word(char *argv)
{
	int		i;
	char	*small_cmd;

//skip whitespace
	i = 0;
	while (argv[i] != '\0' && argv[i] != ' ')
		i++;
	small_cmd = ft_calloc(i + 1, sizeof(char));
	if (!small_cmd)
		return (NULL);
	i = 0;
	while (argv[i] != '\0' && argv[i] != ' ')
	{
printf("argv[i] = %c\n", argv[i]);
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

void	handle_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
