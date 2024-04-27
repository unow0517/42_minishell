/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 15:11:21 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/27 22:12:22 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*iter_env_rest(char **env_split, char *argv, char *small_cmd)
// {
// 	int		i;
// 	char	*cmd;

// 	i = 0;
// 	while (env_split[i])
// 	{
// 		cmd = ft_strjoin(env_split[i], argv);
// 		if (!cmd)
// 			return (NULL);
// 		if (access(cmd, X_OK) != -1)
// 			return (free_split(env_split), free(small_cmd), free(argv), cmd);
// 		i++;
// 		free(cmd);
// 	}
// 	return (NULL);
// }

// void	execute(char *cmd, char *argv, char **env)
// {
// 	char	**ptr;
// 	// char *argv1[] = {"/bin/ls", "-l", NULL};
// 	char *argv1[] = {"/bin/ls", NULL, NULL};
	
// 	ptr = ft_split(argv, ' ');
// 	ft_printf("cmd %s\n", cmd);
// 	ft_printf("ptr %s\n", ptr[0]);
// 	// execve(cmd, ptr, env);
// 	// execve(cmd, ptr, env);
// 	execve(argv1[0], argv1, env);
// 	// perror("execve");
// 	free(ptr[0]);
// 	free(ptr);
// }

// void	execute(char *full_path, char *argv, char **env)
// {
// 	char	**argv_split;
// 	int		i;

// 	i = 0;
// 	argv_split = ft_split(argv, ' ');
// 	argv_split[0] = full_path;
// 	while (argv_split[i] != NULL)
// 	{
// 		i++;
// 	}
// 	argv_split[i - 1] = NULL;
// 	execve(full_path, argv_split, env);

// 	exit(EXIT_FAILURE);
// }

void	execute(char *full_path, char *argv, char **env)
{
	char	**argv_split;
	int		i;

	i = 0;
	if (inputhas(argv, ' '))
	{
		ft_printf("inputhas(argv, ' ')\n");
		// ft_printf("full_path = %s\n", full_path);
		argv_split = ft_split(argv, ' ');
		argv_split[0] = full_path;
		while (argv_split[i] != NULL && argv_split[i][0] != '\0')
		{
			// ft_printf("i: %d\n", i );
			// printf("argv_split[%d]: %s\n",i ,argv_split[i]);
			i++;
		}
		// ft_printf("i_out: %d\n", i );
		// ft_printf("before argv_split[0] = %s\n", argv_split[0]);
		argv_split[i] = NULL;
		// ft_printf("after argv_split[0] = %s\n", argv_split[0]);
		execve(full_path, argv_split, env); //work
		// free_split_thalia(argv_split);
	}
	else
	{
		ft_printf("else\n");
		ft_printf("full_path = %s\n", full_path);

		char *chars[2];
		chars[0] = ft_calloc(ft_strlen(argv), sizeof(char));
		chars[0] = argv;
		chars[1] = NULL;
		ft_printf("chars[0] = %s\n", chars[0]);
		ft_printf("chars[1] = %s\n", chars[1]);
		execve(full_path, chars, env);
		// free(chars[0]);
	}
	// exit(EXIT_FAILURE);
}
// void	execute(char *cmd, char *argv, char **env)
// {
// 	execve(cmd, ft_split(argv, ' '), env);
// 	handle_error("execve");
// }

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
// char	*find_cmd_in_env(char *cmd, char **env)
// {
// 	char	*path_from_env;
// 	int		i;
// 	char	**paths;
// 	char	*slash_cmd;
// 	char	*cmd_path;
// 	int		path_cnt;

// 	path_from_env = "PATH=";
// 	i = 0;
// 	while (env[i] && ft_strncmp(env[i], path_from_env, 5) != 0)
// 		i++;
// 	path_from_env = env[i];
// 	// printf("path_from_env + 5: %s\n", path_from_env + 5);
// 	// printf("path_from_env: %s\n", path_from_env);
// 	paths = ft_split(path_from_env + 5, ':');
// 	path_cnt = cnt_semicolon(path_from_env);
// 	i = 0;
// 	slash_cmd = ft_strjoin("/", cmd);
// 	// printf("slash_cmd: %s\n", slash_cmd);
// 	// while (paths[i])
// 	while (i <= path_cnt)
// 	{
// 		cmd_path = ft_strjoin(paths[i], slash_cmd);
// 		// printf("cmd_path: %s\n\n", cmd_path);
// 		if (access(cmd_path, X_OK) != -1)
// 		{
// 			free(slash_cmd);
// 			free(cmd_path);
// 			free_split(paths, path_cnt);
// 			return (cmd_path);
// 		}
// 		free(cmd_path);
// 		i++;
// 	}
// 	// return (free(paths),  NULL);
// 	// return (free(paths), free(slash_cmd), NULL);
// 	free(slash_cmd);
// 	free_split(paths, path_cnt);
// 	return (NULL);
// 	// return (free(slash_cmd), NULL);
// }

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