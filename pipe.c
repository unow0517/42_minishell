/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:11:21 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/27 11:10:05 by yowoo            ###   ########.fr       */
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

// char	*find_cmd_in_env(char *cmd, char **env)
// {
// 	char	*path_from_env;
// 	int		i;
// 	char	**paths;
// 	char	*slash_cmd;
// 	char	*cmd_path;

// 	i = 0;
// 	path_from_env = "PATH=";
// 	if (ft_strchr(cmd, '/') != NULL)
// 	{
// 		cmd = get_first_word(cmd);
// 		return (cmd);
// 	}
// 	while (env[i] && ft_strncmp(env[i], path_from_env, 5) != 0)
// 		i++;
// 	path_from_env = env[i];
// 	printf("pfe %s\n", path_from_env);
// 	paths = ft_split(path_from_env + 5, ':');
// 	i = 0;
// 	slash_cmd = ft_strjoin("/", cmd);
// 	while (paths[i] && ft_strlen(paths[i]) > 0)
// 	{
// 		cmd_path = ft_strjoin(paths[i], slash_cmd);
// 		if (access(cmd_path, X_OK) != -1)
// 			return (free_split_thalia(paths), free(slash_cmd), cmd_path);
// 		else
// 			free(cmd_path);
// 		i++;
// 	}
// 	return (free_split_thalia(paths), free(slash_cmd), NULL);
// }

char	*find_cmd_in_env_mini(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*slash_cmd;
	char	*cmd_path;

	paths = env;
	i = 0;
	slash_cmd = ft_strjoin("/", cmd);
	if (!paths)
		env_error(cmd);
	while (paths && paths[i] && ft_strlen(paths[i]) > 0)
	{
		cmd_path = ft_strjoin(paths[i], slash_cmd);
		if (access(cmd_path, X_OK) != -1)
			return (free_split_thalia(paths), free(slash_cmd), cmd_path);
		else
			free(cmd_path);
		i++;
	}
	return (free_split_thalia(paths), free(slash_cmd), NULL);
}
