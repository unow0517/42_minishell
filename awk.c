/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:57:28 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 21:51:08 by tsimitop         ###   ########.fr       */
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

// "ls" "-laslalsdl"
// ==47871== 11 bytes in 1 blocks are definitely lost in loss record 3 of 67
// ==47871==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==47871==    by 0x11089E: ft_calloc (in /workspaces/mini_lost/minishell)
// ==47871==    by 0x10F6B4: quote_handler (quotes.c:32)
// ==47871==    by 0x10BE8B: initialize_cmd_options_helper (parsing_helper.c:62)
// ==47871==    by 0x10BF2C: initialize_cmd_options (parsing_helper.c:77)
// ==47871==    by 0x10BA74: set_executable_nodes (parsing.c:61)
// ==47871==    by 0x10B92F: parse_tokens (parsing.c:35)
// ==47871==    by 0x10B8EC: parse_input (parsing.c:22)
// ==47871==    by 0x10B42A: inpt_handler (inpt_handler.c:26)
// ==47871==    by 0x10B566: main (minishell.c:25)