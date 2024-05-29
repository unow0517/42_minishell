/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_cases_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:33:01 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 11:37:06 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ft_is_builtin(char *s)
{
	if (!s)
		return (false);
	if (ft_strncmp(s, "\"echo\"", 6) == 0 || ft_strncmp(s, "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(s, "\"cd\"", 4) == 0 || ft_strncmp(s, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(s, "\"pwd\"", 5) == 0 || ft_strncmp(s, "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(s, "\"export\"", 8) == 0 || \
	ft_strncmp(s, "export", 6) == 0)
		return (true);
	else if (ft_strncmp(s, "\"unset\"", 7) == 0 || \
	ft_strncmp(s, "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(s, "\"env\"", 5) == 0 || ft_strncmp(s, "env", 3) == 0)
		return (true);
	else if (ft_strncmp(s, "\"exit\"", 6) == 0 || ft_strncmp(s, "exit", 4) == 0)
		return (true);
	else if (ft_strncmp(s, "\"pwd\"", 5) == 0 || ft_strncmp(s, "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(s, "\"history\"", 9) == 0 || \
	ft_strncmp(s, "history", 7) == 0)
		return (true);
	return (false);
}
