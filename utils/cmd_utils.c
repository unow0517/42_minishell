/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:32:23 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 11:34:32 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	num_of_remaining_cmds(t_command *cur) //check if needed
// {
// 	int	counter;

// 	counter = 0;
// 	while (cur)
// 	{
// 		cur = cur->next;
// 		counter++;
// 	}
// 	return (counter);
// }

int	num_of_total_cmds(t_command *cur)
{
	int	counter;

	counter = 0;
	while (cur)
	{
		cur = cur->next;
		counter++;
	}
	return (counter);
}

void	finalise_node(t_shell *shell_info, t_command *cmd_node)
{
	if (cmd_node->is_builtin == 0)
		init_cmds_in_struct(cmd_node, cmd_node->to_split);
	cmd_add_back(&shell_info->first_command, cmd_node);
	quote_removal_in_exec_arg(cmd_node);
}
