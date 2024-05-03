/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:39:36 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/03 19:49:04 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	ft_printf("current token = %p\n", token);
	ft_printf("token->input = %s\n", token->input);
	ft_printf("token->len = %i\n", token->len);
	ft_printf("token->i = %i\n", token->idx);
	// ft_printf("token->user_input_element = %s\n", token->user_input_element);
	ft_printf("token->content = %s\n", &token->input[token->idx]);
	ft_printf("token->token_type = %i\n", token->token_type);
	ft_printf("token->next = %p\n", token->next);
}

void	print_linked_tokens(t_token *token)
{
	while (token)
	{
		ft_printf("________________________________________________________\n");
		print_token(token);
		token = token->next;
	}
}

void	print_split(char **str)
{
	int i = 0;

	while (str[i])
	{
		printf("str[%i] = %s\n", i, str[i]);
		i++;
	}
}
