/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:57:28 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 21:42:19 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	nullify_ints(int *inside_sq, int *inside_dq, int *i)
{
	*i = 0;
	*inside_dq = 0;
	*inside_sq = 0;
}

t_token	*handle_awk(t_token *iterate, t_command *cmd_node)
{
	int			i;
	int			sq;
	int			dq;

	nullify_ints(&sq, &dq, &i);
	cmd_node->cmd = get_first_word(iterate->content);
	iterate = iterate->next;
	dq = 0;
	sq = 0;
	nullify_ints(&sq, &dq, &i);
	cmd_node->to_split = ft_substr(iterate->content, 0, awk_restlen(iterate, &sq, &dq));
	iterate = skip_awk(iterate, &sq, &dq);
	return (iterate);
}

// awk '/int/ { print $1 }' minishell.c "pipe.c" | grep i
// awk '/int/ { print }' minishell.c
// rm_q_in_fullcmd (quotes_one.c:52)
// quote_removal_in_exec_arg (quotes_one.c:75)
// finalise_node (cmd_utils.c:46)