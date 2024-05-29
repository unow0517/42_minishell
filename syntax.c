/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:59:12 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 11:59:21 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unexpected_token(t_shell *shell_info, char *flag)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (shell_info->tokens->token_type == WORD)
		ft_putstr_fd(get_first_word(shell_info->tokens->content), 2);
	else
		ft_putstr_fd(flag, 2);
	ft_putstr_fd("'\n", 2);
	shell_info->syntax_error = true;
	*shell_info->status = 258;
}

void	quote_error(t_shell *shell_info)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error: ", 2);
	ft_putstr_fd("can't handle unclosed quotes\n", 2);
	*shell_info->status = 258;
}

void	syntax_error_check(t_shell *shell_info)
{
	t_token	*iter;
	int		dq;
	int		sq;

	dq = 0;
	sq = 0;
	if (!shell_info->tokens)
		return ;
	iter = shell_info->tokens;
	if (syntax_error_at_start(iter) == true)
		syntax_error_at_start_msg(shell_info, iter);
	else
	{
		while (iter && iter->next)
		{
			update_quote_state(iter, &sq, &dq, 0);
			if (has_redir_twice(iter, dq, sq) == true)
				iter = twice_redir_case(shell_info, iter);
			else if (has_double_pipe(iter, dq, sq) == true)
				iter = double_pipe_case(shell_info, iter);
			if (iter)
				iter = iter->next;
		}
	}
}

bool	syntax_error_at_start(t_token *iter)
{
	if ((iter->token_type == PIPE && !iter->next) || \
	(iter->token_type == PIPE && iter->next->token_type != PIPE))
		return (true);
	else if (iter->token_type == PIPE && iter->next && \
	iter->next->token_type == PIPE)
		return (true);
	else if (is_redir(iter->token_type) == true && !iter->next)
		return (true);
	return (false);
}

void	syntax_error_at_start_msg(t_shell *shell_info, t_token *iter)
{
	if ((iter->token_type == PIPE && !iter->next) || \
	(iter->token_type == PIPE && iter->next->token_type != PIPE))
		unexpected_token(shell_info, "|");
	else if (iter->token_type == PIPE && iter->next && \
	iter->next->token_type == PIPE)
		unexpected_token(shell_info, "|");
	else if (is_redir(iter->token_type) == true && !iter->next)
		unexpected_token(shell_info, "newline");
}
