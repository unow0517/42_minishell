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

t_token	*create_word_token(t_shell *shell_info, int i)
{
	int		len;
	int		start_pos;
	t_token	*cur;

	len = 0;
	start_pos = i;
	if (shell_info->user_input[i] != '\0' && is_ws(shell_info->user_input[i]) == false)
	{
		cur = ft_calloc(sizeof(t_token), 1);
		if (!cur)
			return (NULL);
	}
	while (shell_info->user_input[i] != '\0' && is_ws(shell_info->user_input[i]) == false)
	{
		if (is_metacharacter(shell_info->user_input[i]) == true)
			break;
		i++;
		len++;
	}
	cur->idx = start_pos;
	cur->input = shell_info->user_input;
	cur->token_type = WORD;
	cur->len = len;
	cur->content = &shell_info->user_input[start_pos];
	cur->next = NULL;
	return (cur);
}

t_token	*create_single_token(t_shell *shell_info, int i)
{
	t_token *cur;

	cur = NULL;
	if (is_metacharacter(shell_info->user_input[i]) == true)
	{
		cur = ft_calloc(sizeof(t_token), 1);
		if (!cur)
			return (NULL);
		cur->idx = i;
		if (shell_info->user_input[i] == '>')
			cur->token_type = S_MORE;
		else if (shell_info->user_input[i] == '<')
			cur->token_type = S_LESS;
		else if (shell_info->user_input[i] == '|')
			cur->token_type = PIPE;
		else if (shell_info->user_input[i] == '\'')
			cur->token_type = S_QUOTE;
		else if (shell_info->user_input[i] == '"')
			cur->token_type = D_QUOTE;
		cur->input = shell_info->user_input;
		cur->content = &shell_info->user_input[i];
		i++;
		cur->len = 1;
		cur->next = NULL;
	}
	return (cur);
}

//CREATE TOKEN FOR <<, >>
t_token	*create_double_token(t_shell *shell_info, int i)
{
	t_token *cur;

	cur = NULL;
	if (is_double(shell_info, i) == true)
	{
		cur = ft_calloc(sizeof(t_token), 1);
		if (!cur)
			return (NULL);
		cur->idx = i;
		if (shell_info->user_input[i] == '>' && shell_info->user_input[i + 1] == '>')
			cur->token_type = D_MORE;
		else if (shell_info->user_input[i] == '<' && shell_info->user_input[i + 1] == '<')
			cur->token_type = D_LESS;
		else
			cur->token_type = NO_TOKEN;
		cur->input = shell_info->user_input;
		cur->content = &shell_info->user_input[i];
		i = i + 2;
		cur->len = 2;
		cur->next = NULL;
	}
	return (cur);
}

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
			break;
		cur = allocate_token(shell_info, cur, i);
		if (cur == NULL)
			break ;
		i = cur->idx + cur->len;
		token_add_back(&shell_info->tokens, cur);
		if (shell_info->user_input[i] == '\0')
			break;
		cur = cur->next;
	}
}
