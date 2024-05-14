/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:03:00 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/30 19:00:38 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ABS PATH
void	run_cd(char *inpt, t_shell *shell_info)
{
	char	*path_input;
	char	cwd[1024];
	char	*cwd_input;

	// char	*slash_path;
	// char	*path;

	getcwd(cwd, sizeof(cwd));
	path_input = inpt + 3;
	if (access(path_input, R_OK) != -1)
	{
		cwd_input = ft_substr(path_input, 0, ft_strlen(cwd));
		if (ft_strncmp(cwd_input, cwd, ft_strlen(cwd_input)) == 0)
		{
			ft_memset(shell_info->cwd, 0, 1024);
			ft_strlcat(shell_info->cwd, path_input, 1024);
			// shell_info->cwd = ft_strdup(path_input);
		}
		else
			ft_printf("minishell: cd : %s: Folder exist but absolute path is required\n", path_input);	
	}
	else
		ft_printf("minishell: cd : %s: Only absolute path is available\n", path_input);
	// if (cwd)
	// 	free(cwd);
}

		// printf("substr: %s\n", ft_substr(path_input, 0, ft_strlen(cwd)));
		// printf("substrlen: %zu\n", ft_strlen(ft_substr(path_input, 0, ft_strlen(cwd))));
		// printf("cwdlen: %zu\n", ft_strlen(cwd));
		// printf("if %d\n", ft_substr(path_input, 0, ft_strlen(cwd)) == cwd);
		// printf("cwd_input: %s\n", cwd_input);
		// printf("cwd: %s\n", cwd);
		// printf("cwd: %d\n", ft_strncmp(cwd_input, cwd, ft_strlen(cwd_input)));


// //RELATIVE PATH
// void	run_cd(char *inpt, t_mini *shell_info)
// {
// 	char	*rlt_path;
// 	char	cwd[1024];
// 	char	*slash_path;
// 	char	*path;

// 	// getcwd(cwd, sizeof(cwd));
// 	// printf("cwd: %s\n", cwd);
// 	rlt_path = inpt + 3;
// 	slash_path = ft_strjoin("/", rlt_path);
// 	if (access(ft_strjoin(cwd, slash_path), R_OK) != -1)
// 	{
// 		shell_info->cwd = ft_strjoin(cwd, slash_path);
// 	}
// 	else if (!(*rlt_path == '.' && *(rlt_path + 1) == '/')) //case of cd Nolibft
// 		ft_printf("minishell: cd : %s: No such file or directory\n", rlt_path);
// 	else if (*rlt_path == '.' && *(rlt_path + 1) == '.')
	
// 	else // case of cd ./Libft 
// 	{
// 		path = ft_strjoin(cwd, rlt_path + 1);
// 		if (access(path, R_OK) != -1)
// 			shell_info->cwd = path;
// 		free(path);
// 	}
// 	free(slash_path);
// }
