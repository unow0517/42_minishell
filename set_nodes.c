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

void	input_types(char *inpt, t_shell *info, t_token *first_token)
{
	int	i;
	t_token	*cur;

	i = 0;
	cur = NULL;
	cur = first_token;
	while (inpt && inpt[i])
	{
		cur = ft_calloc(sizeof(t_token), 1);
		cur->input = ft_calloc(ft_strlen(inpt) + 1, sizeof(char));
		if (!cur->input)
			perror("calloc failed");
		cur->input = inpt;
		token_add_back(info->first_token_node, cur);
		i = skip_whitespace(inpt, i);
		if (inpt[i] == '\0')
			break;
		if (!(ft_isalpha(inpt[i])) && !(ft_isdigit(inpt[i])) && !(inpt[i] == '-'))
			i = set_token_not_word(inpt, i, cur);
		else if ((inpt[i] == '-') || (ft_isdigit(inpt[i])) || (ft_isalpha(inpt[i])))
			i = set_token_word(inpt, i, cur);
		i++;
		cur = cur->next;
	}
	// print_linked_tokens(*(info->first_token_node));
}

int	set_token_word(char *inpt, int i, t_token *token)
{
	int	len;

	len = 0;
	token->i = i;
	while (inpt[i] != '\0' && ((ft_isalpha(inpt[i])) || (ft_isdigit(inpt[i])) \
	|| (inpt[i] == '-')))
	{
		len++;
		i++;
	}
	token->len = len;
	token->token_type = WORD;
	token->next = NULL;
	return (i);
}

int	set_token_not_word(char *inpt, int i, t_token *token)
{
	token->i = i;
	if (inpt[i] == '|' || (inpt[i] == '>' && inpt[i + 1] != '>') || (inpt[i] \
	== '<' && inpt[i + 1] != '<') || (inpt[i] == '\'') || (inpt[i] == '"'))
		i++;
	else if ((inpt[i] == '>' && inpt[i + 1] == '>') || (inpt[i] == '<' && \
	inpt[i + 1] == '<'))
		i = i + 2;
	if (inpt[i] == '|')
		token->token_type = PIPE;
	else if (inpt[i] == '>' && inpt[i + 1] != '>')
		token->token_type = S_MORE;
	else if (inpt[i] == '<' && inpt[i + 1] != '<')
		token->token_type = S_LESS;
	else if (inpt[i] == '\'')
		token->token_type = S_QUOTE;
	else if (inpt[i] == '"')
		token->token_type = D_QUOTE;
	else if (inpt[i] == '>' && inpt[i + 1] == '>')
		token->token_type = D_MORE;
	else if (inpt[i] == '<' && inpt[i + 1] == '<')
		token->token_type = D_LESS;
	token->next = NULL;
	return (i);
}
