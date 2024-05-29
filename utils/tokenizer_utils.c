/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:28:48 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 13:20:34 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	do_the_rest_word(t_token *cur, int len, int start_pos)
{
	cur->idx = start_pos;
	cur->token_type = WORD;
	cur->len = len;
}

t_token	*create_word_token(t_shell *sh_i, int i)
{
	int		len;
	int		start_pos;
	t_token	*cur;

	len = 0;
	start_pos = i;
	if (sh_i->user_input[i] != '\0' && is_ws(sh_i->user_input[i]) == false)
	{
		cur = ft_calloc(sizeof(t_token), 1);
		if (!cur)
			return (NULL);
	initialize_token(cur);
	
	}
	while (sh_i->user_input[i] != '\0' && is_ws(sh_i->user_input[i]) == false)
	{
		if (is_metacharacter(sh_i->user_input[i]) == true)
			break ;
		i++;
		len++;
	}
	cur->input = sh_i->user_input;
	do_the_rest_word(cur, len, start_pos);
	cur->content = &sh_i->user_input[start_pos];
	cur->next = NULL;
	return (cur);
}

static int	do_the_rest_single(t_token *cur)
{
	cur->len = 1;
	cur->next = NULL;
	return (1);
}

t_token	*create_single_token(t_shell *shell_info, int i)
{
	t_token	*cur;

	cur = NULL;
	if (is_metacharacter(shell_info->user_input[i]) == true)
	{
		cur = ft_calloc(sizeof(t_token), 1);
		if (!cur)
			return (NULL);
	initialize_token(cur);
	
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
		i += do_the_rest_single(cur);
	}
	return (cur);
}

//CREATE TOKEN FOR <<, >>
t_token	*create_double_token(t_shell *shell_info, int i)
{
	t_token	*cur;

	cur = NULL;
	if (is_double(shell_info, i) == true)
	{
		cur = ft_calloc(sizeof(t_token), 1);
		if (!cur)
			return (NULL);
	initialize_token(cur);
		cur->idx = i;
		if (shell_info->user_input[i] == '>' && \
		shell_info->user_input[i + 1] == '>')
			cur->token_type = D_MORE;
		else if (shell_info->user_input[i] == '<' && \
		shell_info->user_input[i + 1] == '<')
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
