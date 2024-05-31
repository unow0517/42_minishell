/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:11:21 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/31 14:37:06 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cnt_semicolon(char *string)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (string[i] != '\0')
	{
		if (string[i] == ':')
			cnt++;
		i++;
	}
	return (cnt);
}

void	free_split(char **string, int n)
{
	while (n >= 0)
	{
		free(string[n]);
		n--;
	}
	free(string);
}

char	*find_cmd_in_env_mini(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*slash_cmd;
	char	*cmd_path;

	paths = env;
	i = 0;
	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (get_first_word(cmd));
	slash_cmd = ft_strjoin("/", cmd);
	if (!paths)
		return (free(slash_cmd), slash_cmd = NULL, NULL);
	while (paths && paths[i] && ft_strlen(paths[i]) > 0)
	{
		cmd_path = ft_strjoin(paths[i], slash_cmd);
		if (access(cmd_path, X_OK) != -1)
			return (free(slash_cmd), cmd_path);
		else
			free(cmd_path);
		i++;
	}
	return (free(slash_cmd), NULL);
}
