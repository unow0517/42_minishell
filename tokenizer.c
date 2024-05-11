/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:21:45 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/25 15:24:16 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_word_token(t_shell *shell_info, int i)
{
	int		len;
	int		start_pos;
	t_token	*cur;
	char	*inpt;

	len = 0;
	start_pos = i;
	inpt = shell_info->user_input;
	if (inpt[i] != '\0' && is_ws(inpt[i]) == false)
	{
		cur = ft_calloc(sizeof(t_token), 1);
		if (!cur)
		{
			// free stuff!!!!
			return (NULL);
		}
	}
	while (inpt[i] != '\0' && is_ws(inpt[i]) == false)
	{
		if (is_metacharacter(inpt[i]) == true)
		{
			// printf("inpt[%d] = %c\tlen = %i\n", i, inpt[i], len);
			// i--;
			// len--;
			break;
		}
		i++; //check for < > | ' " for input without gaps
		len++;
	}
	cur->idx = start_pos;
	cur->input = inpt;
	cur->token_type = WORD;
	cur->len = len;
	cur->content = &inpt[start_pos];
	cur->next = NULL;
	return (cur);
}

t_token	*create_single_token(t_shell *shell_info, int i)
{
	t_token *cur;
	char	*inpt;

	cur = NULL;
	inpt = shell_info->user_input;
	// if (!(inpt[i] == '|') && !(inpt[i] == '>') && !(inpt[i] == '<') && !(inpt[i] == '\'') && !(inpt[i] == '"'))
	// 	return (NULL);
	if (is_metacharacter(inpt[i]) == true)
	{
		cur = ft_calloc(sizeof(t_token), 1);
		if (!cur)
		{
			// free stuff!!!!
			return (NULL);
		}
		cur->idx = i;
		if (inpt[i] == '>')
			cur->token_type = S_MORE;
		else if (inpt[i] == '<')
			cur->token_type = S_LESS;
		else if (inpt[i] == '|')
			cur->token_type = PIPE;
		else if (inpt[i] == '\'')
			cur->token_type = S_QUOTE;
		else if (inpt[i] == '"')
			cur->token_type = D_QUOTE;
		else
			cur->token_type = NO_TOKEN;
		cur->input = inpt;
		cur->content = &inpt[i];
		i++;
		cur->len = 1;
		cur->next = NULL;
	}
	return (cur);
}

t_token	*create_double_token(t_shell *shell_info, int i)
{
	t_token *cur;
	char	*inpt;

	cur = NULL;
	inpt = shell_info->user_input;
	// if (!(inpt[i] == '>' && inpt[i + 1] == '>') && !(inpt[i] == '<' && inpt[i + 1] == '<'))
	// 	return (NULL);
	if ((inpt[i] == '>' && inpt[i + 1] == '>') || (inpt[i] == '<' && inpt[i + 1] == '<'))
	{
		cur = ft_calloc(sizeof(t_token), 1);
		if (!cur)
		{
			// free stuff!!!!
			return (NULL);
		}
		cur->idx = i;
		if (inpt[i] == '>' && inpt[i + 1] == '>')
			cur->token_type = D_MORE;
		else if (inpt[i] == '<' && inpt[i + 1] == '<')
			cur->token_type = D_LESS;
		else
			cur->token_type = NO_TOKEN;
		cur->input = inpt;
		cur->content = &inpt[i];
		i = i + 2;
		cur->len = 2;
		cur->next = NULL;
	}
	return (cur);
}


// create_word

int	create_tokens(t_shell *shell_info)
{
	int		i;
	t_token	*cur;
	char	*inpt;

	i = 0;
	cur = NULL;
	inpt = shell_info->user_input;
	if (!shell_info->tokens)
		shell_info->tokens = cur;
	while (inpt && inpt[i] != '\0') // && inpt[i] != EOF
	{
		i = skip_whitespace(inpt, i);
		if (inpt[i] == '\0')
			break;
		cur = create_double_token(shell_info, i);
		if (cur == NULL)
			cur = create_single_token(shell_info, i);
		if (cur == NULL)
			cur = create_word_token(shell_info, i);
		if (cur == NULL)
			break ;
		if (cur->token_type == NO_TOKEN)
		{
			free(cur);
			break;
		}
		i = cur->idx + cur->len;
		token_add_back(&shell_info->tokens, cur);
		if (inpt[i] == '\0')
			break;
		// i++;
		cur = cur->next;
	}
	// print_linked_tokens(shell_info->tokens);
	if (cur)
		return (0);
	else
		return (1);
}

// la -l > f1 << END | grep hi | cat > out
// la -l < f1 < f2 < f3 > f1 << END | grep hi | cat > out
