/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:08:36 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/29 15:54:58 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_back(t_token **first_token, t_token *new)
{
	t_token	*end;
// ft_printf("utils.c_____________INPUT TYPES DEBUGGING_________________\n");

	if (!first_token || !new)
		return ;
	if (!*first_token)
	{
// ft_printf("entered first token loop\n");
		*first_token = new;
		return ;
	}
// ft_printf("set nodes.c____token_add_back\n");
	end = token_last(*first_token);
	end->next = new;
}

t_token	*token_last(t_token *token)
{
	int i = 0;
	if (!token)
	{
		return (NULL);
	}
	while (token && token->next)
	{
// ft_printf("1: set nodes.c____token_last_i = %d\n", i);
// ft_printf("1: set nodes.c____token = %p\n", token);
		token = token->next;
// ft_printf("2: set nodes.c____token = %p\n", token);
// ft_printf("2: set nodes.c____token_last_i = %d\n", i);

i++;
	}
// ft_printf("set nodes.c____token_last______DONE_________________\n", i);
	return (token);
}


int	skip_whitespace(char *inpt, int i)
{
	while (inpt[i] != '\0' && (inpt[i] == ' ' || inpt[i] == '\t' || inpt[i] == '\r' ||\
	 inpt[i] == '\n' || inpt[i] == '\v' || inpt[i] == '\f'))
	 	i++;
	return (i);
}
