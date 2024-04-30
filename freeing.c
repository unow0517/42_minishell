/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:13:23 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/30 19:37:06 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token **tokens)
{
	t_token	*del;
	t_token	*temp;

	del = *tokens;
	while (del)
	{
		temp = del;
		del = del->next;
		free(temp);
	}
	*tokens = NULL;
	// free(tokens);
}
