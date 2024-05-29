/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_cases_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:32:34 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 11:32:58 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_ws(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool	quotes_even(char *input)
{
	int		i;
	int		q_counter;
	int		inside_sq;
	int		inside_dq;

	nullify_ints_four(&inside_sq, &inside_dq, &i, &q_counter);
	if (!input)
		return (true);
	while (input[i] != '\0')
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if ((inside_dq + inside_sq) == 0 || \
			(inside_sq == 1 && input[i] == '\'') || \
			(inside_dq == 1 && input[i] == '"'))
			{
				update_quote_state_str(input, &inside_sq, &inside_dq, i);
				q_counter++;
			}
		}
		i++;
	}
	if (q_counter % 2 == 0)
		return (true);
	return (false);
}

bool	is_double(t_shell *shell_info, int i)
{
	if ((shell_info->user_input[i] == '>' && \
	shell_info->user_input[i + 1] == '>') || \
	(shell_info->user_input[i] == '<' && shell_info->user_input[i + 1] == '<'))
		return (true);
	return (false);
}

bool	has_double_pipe(t_token *iter, int dq, int sq)
{
	if (iter->token_type == PIPE && iter->next && \
	iter->next->token_type == PIPE && dq == 0 && sq == 0)
		return (true);
	return (false);
}

t_token	*double_pipe_case(t_shell *shell_info, t_token *iter)
{
	if (shell_info->tokens->token_type == WORD)
		unexpected_token(shell_info, \
		get_first_word(shell_info->tokens->content));
	else
		unexpected_token(shell_info, "|");
	while (iter && iter->token_type == PIPE)
		iter = iter->next;
	return (iter);
}
