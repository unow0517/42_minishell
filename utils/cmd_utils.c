/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:32:23 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 12:37:36 by tsimitop         ###   ########.fr       */
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

void	init_cmds_in_struct(t_command *cmd_node, char *to_split)
{
	char	*to_full_cmd;
	char	*temp_cmd;

	to_full_cmd = NULL;
	temp_cmd = NULL;
	if (cmd_node->cmd)
		temp_cmd = ft_strjoin(cmd_node->cmd, " ");
	if (cmd_node->cmd && to_split)
		to_full_cmd = ft_strjoin(temp_cmd, to_split);
	if (cmd_node->cmd && to_full_cmd)
		cmd_node->full_cmd = split_ms(to_full_cmd, ' ');
	if (to_split)
		cmd_node->options = split_ms(to_split, ' ');
	if (temp_cmd)
		free(temp_cmd);
	if (to_full_cmd)
		free(to_full_cmd);
}

void	initialise_cmd_node(t_command *cmd_node)
{
	cmd_node->cmd = NULL;
	cmd_node->options = NULL;
	cmd_node->full_cmd = NULL;
	cmd_node->input_fd = -1;
	cmd_node->output_fd = -1;
	cmd_node->is_heredoc = 0;
	pipe(cmd_node->fd);
	cmd_node->file_not_found = 0;
	cmd_node->filename = NULL;
	cmd_node->is_builtin = false;
	cmd_node->to_split = "";
	cmd_node->is_builtin = 0;
	cmd_node->builtin_type = NULL;
	cmd_node->builtin_arg = NULL;
	cmd_node->next = NULL;
}
