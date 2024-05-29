/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_cases.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:32:47 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 11:36:46 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_metacharacter(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '"' || c == '\'')
		return (true);
	return (false);
}

bool	is_metacharacter_type(int i)
{
	if (i == PIPE || i == S_QUOTE || i == D_QUOTE || i == S_LESS || \
	i == S_MORE || i == D_LESS || i == D_MORE)
		return (true);
	return (false);
}

bool	is_redir(int i)
{
	if (i == S_LESS || i == S_MORE || i == D_LESS || i == D_MORE)
		return (true);
	return (false);
}

bool	is_redir_pipe(t_token_type i)
{
	if (i == S_LESS || i == S_MORE || i == D_LESS || i == D_MORE || i == PIPE)
		return (true);
	return (false);
}

bool	is_redir_pipe_char(char i)
{
	if (i == '<' || i == '>' || i == '|')
		return (true);
	return (false);
}
