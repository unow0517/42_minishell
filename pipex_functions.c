/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:36:23 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/25 16:40:52 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *argv, char **env)
{
	char	*path;
	char	*cmd;
	int		i;

	i = 0;
	path = "PATH=";
	if (ft_strchr(argv, '/') != NULL)
	{
		cmd = get_directory_name(argv);
		return (cmd);
	}
	while (env[i] && ft_strncmp(env[i], path, 5) != 0)
		i++;
	path = env[i];
	cmd = iter_env(path, argv);
	return (cmd);
}

char	*get_directory_name(char *argv)
{
	int		i;
	char	*small_cmd;

	i = 0;
	while (argv[i] != '\0' && argv[i] != ' ')
		i++;
	small_cmd = ft_calloc(i + 1, sizeof(char));
	if (!small_cmd)
		return (NULL);
	i = 0;
	while (argv[i] != '\0' && argv[i] != ' ')
	{
		small_cmd[i] = argv[i];
		i++;
	}
	return (small_cmd);
}

char	*iter_env(char *path, char *argv)
{
	int		i;
	char	**env_split;
	char	*cmd;
	char	*small_cmd;
	char	*ret_str;

	i = 0;
	small_cmd = get_directory_name(argv);
	if (!small_cmd)
	{
		ret_str = ft_strjoin("pipex: ", argv);
		if (!ret_str)
			return (NULL);
		handle_error_free(ret_str);
	}
	argv = ft_strjoin("/", small_cmd);
	env_split = ft_split(path + 5, ':');
	while (env_split[i])
	{
		cmd = ft_strjoin(env_split[i], argv);
		if (!cmd)
			return (NULL);
		if (access(cmd, X_OK) != -1)
			return (free_split(env_split), free(small_cmd), free(argv), cmd);
		i++;
		free(cmd);
	}
	return (free_split(env_split), free(small_cmd), free(argv), NULL);
}

void	execute(char *cmd, char *argv, char **env)
{
	execve(cmd, ft_split(argv, ' '), env);
	handle_error("execve");
}

//minishell
char	*find_cmd_in_env(char *cmd, char **env)
{
	char	*path_from_env;
	int		i;
	char	**paths;
	char	*slash_cmd;
	char	*cmd_path;

	i = 0;
	path_from_env = "PATH=";
	while (env[i] && ft_strncmp(env[i], path_from_env, 5) != 0)
		i++;
	path_from_env = env[i];
	paths = ft_split(path_from_env + 5, ':');
	i = 0;
	slash_cmd = ft_strjoin("/", cmd);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], slash_cmd);
		if (access(cmd_path, X_OK) != -1)
			return (free(paths), free(slash_cmd), cmd_path);
		else
			free(cmd_path);
		i++;
	}
	return (free(paths), free(slash_cmd), NULL);
}

void	close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

// int	handle_exit(int status)
// {
// 	if (WIFEXITED(status))
// 		status = WEXITSTATUS(status);
// 	else
// 		status = EXIT_FAILURE;
// 	return (status);
// }

void	handle_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

void	handle_error_free(char *str)
{
	perror(str);
	if (str)
		free(str);
	exit(EXIT_FAILURE);
}
