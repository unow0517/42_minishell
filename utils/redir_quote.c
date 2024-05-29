/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:33:11 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 11:33:14 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	has_redir_twice(t_token *iter, int dq, int sq)
{
	if (is_redir(iter->token_type) && \
	is_redir(iter->next->token_type) && dq == 0 && sq == 0)
		return (true);
	return (false);
}

t_token	*twice_redir_case(t_shell *shell_info, t_token *iter)
{
	if ((iter->token_type == S_MORE && iter->next->token_type == S_LESS) || \
	(iter->token_type == S_LESS && iter->next->token_type == S_MORE))
		unexpected_token(shell_info, "<>");
	else if (iter->next->token_type == D_LESS || \
	iter->next->token_type == S_LESS)
		unexpected_token(shell_info, "<");
	else if (iter->next->token_type == D_MORE || \
	iter->next->token_type == S_MORE)
		unexpected_token(shell_info, ">");
	while (iter && is_redir(iter->token_type))
		iter = iter->next;
	return (iter);
}

void	update_quote_state_token(t_token *cur, int *sq, int *dq)
{
	if (cur->token_type == S_QUOTE && *sq == 0)
		*sq = 1;
	else if (cur->token_type == S_QUOTE && *sq == 1)
		*sq = 0;
	if (cur->token_type == D_QUOTE && *dq == 0)
		*dq = 1;
	else if (cur->token_type == D_QUOTE && *dq == 1)
		*dq = 0;
}

void	update_quote_state(t_token *cur, int *sq, int *dq, int i)
{
	if (cur->content[i] == '\'' && *sq == 0)
		*sq = 1;
	else if (cur->content[i] == '\'' && *sq == 1)
		*sq = 0;
	if (cur->content[i] == '"' && *dq == 0)
		*dq = 1;
	else if (cur->content[i] == '"' && *dq == 1)
		*dq = 0;
}
