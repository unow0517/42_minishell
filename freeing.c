/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 18:13:23 by tsimitop          #+#    #+#             */
/*   Updated: 2024/04/27 18:13:36 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_small_linked(t_shell *shell_info)
{
	t_token	*del;
	t_token	*temp;

	del = *(shell_info->first_token_node);
	while (del)
	{
		temp = del;
		del = del->next;
		free(temp);
	}
	free(shell_info->first_token_node);
}
