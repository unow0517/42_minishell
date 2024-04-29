/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:08:36 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/25 16:23:12 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_back(t_token **first_token, t_token *new)
{
	t_token	*end;

	if (!first_token || !new)
		return ;
	if (!*first_token)
	{
		*first_token = new;
		return ;
	}
	end = token_last(*first_token);
	end->next = new;
}

t_token	*token_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->next)
		token = token->next;
	return (token);
}


int	skip_whitespace(char *inpt, int i)
{
	while (inpt[i] != '\0' && (inpt[i] == ' ' || inpt[i] == '\t' || inpt[i] == '\r' ||\
	 inpt[i] == '\n' || inpt[i] == '\v' || inpt[i] == '\f'))
	 	i++;
	return (i);
}
