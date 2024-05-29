/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:25:38 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/23 17:25:38 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*allocate_token(t_shell *shell_info, t_token *cur, int i)
{
	cur = create_double_token(shell_info, i);
	if (cur == NULL)
		cur = create_single_token(shell_info, i);
	if (cur == NULL)
		cur = create_word_token(shell_info, i);
	return (cur);
}

void	create_tokens(t_shell *shell_info)
{
	int		i;
	t_token	*cur;

	i = 0;
	cur = NULL;
	if (!shell_info->tokens)
		shell_info->tokens = cur;
	while (shell_info->user_input && shell_info->user_input[i] != '\0')
	{
		i = skip_whitespace(shell_info->user_input, i);
		if (shell_info->user_input[i] == '\0')
			break ;
		cur = allocate_token(shell_info, cur, i);
		if (cur == NULL)
			break ;
		i = cur->idx + cur->len;
		token_add_back(&shell_info->tokens, cur);
		if (shell_info->user_input[i] == '\0')
			break ;
		cur = cur->next;
	}
}

void	initialize_token(t_token *tok)
{
	tok->input = NULL;
	tok->len = 0;
	tok->idx = 0;
	tok->content = NULL;
	tok->token_type = NO_TOKEN;
	tok->next = NULL;
}
