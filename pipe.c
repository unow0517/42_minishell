/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:11:21 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/29 13:21:50 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char *cmd, char *argv, char **env)
{
	execve(cmd, ft_split(argv, ' '), env);
	handle_error("execve");
}

// void	run_pipe(char *inpt)
void	run_pipe(char *inpt, char **argv, char **env)
{
	char	**subcmds;
	char	*path_from_env;
	int		i;
	char	**paths;
	char	*first_cmd;
	char	*cmd_path;

	subcmds = ft_split(inpt, '|');
	//FIND PROPER BIN FOLDER FOR 
	path_from_env = "PATH=";
	i = 0;
	while (env[i] && ft_strncmp(env[i], path_from_env, 5) != 0)
		i++;
	//PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/yowoo/.brew/bin
	path_from_env = env[i];
	paths = ft_split(path_from_env + 5, ':');
	i = 0;
	printf("%s\n", paths[0]);
	first_cmd = ft_split(subcmds[0],' ')[0];
	first_cmd = ft_strjoin("/",first_cmd);
	printf("%s\n", first_cmd);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], first_cmd);
		// printf("%s\n", cmd_path);
		if (access(cmd_path, X_OK) != -1)
		{
			printf("first_cmd found\n");
			break ;
		}
		i++;
	}
	// execute(cmd_path, ft_split(first_cmd,' ')[0], env);
	execute("ls -la", ft_split(first_cmd,' ')[0], env);
	(void)argv;
}

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
	free(string);;
}

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
	while (paths[i] && ft_strlen(paths[i]) > 0)
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