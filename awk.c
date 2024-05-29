/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   awk.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:57:28 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 13:51:56 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	awk_data_init(t_awk_data *data)
{
	data->to_split_options = NULL;
	data->to_split_options_rest = NULL;
	data->temp = NULL;
}

static void	awk_free(t_awk_data *data)
{
	if (data->temp)
		free(data->temp);
	if (data->to_split_options)
		free(data->to_split_options);
	if (data->to_split_options_rest)
		free(data->to_split_options_rest);
}

static void	nullify_ints(int *inside_sq, int *inside_dq, int *i)
{
	*i = 0;
	*inside_dq = 0;
	*inside_sq = 0;
}

t_token	*handle_awk(t_token *iterate, t_command *cmd_node)
{
	int			i;
	int			h;
	int			sq;
	int			dq;
	t_awk_data	data;

	nullify_ints(&sq, &dq, &i);
	awk_data_init(&data);
	cmd_node->cmd = get_first_word(iterate->content);
	iterate = iterate->next;
	data.to_split_options = ft_calloc(awk_sqlen(iterate) + 1, sizeof(char));
	dq = 0;
	sq = 0;
	h = awk_sq_part(&data, iterate);
	data.to_split_options_rest = ft_calloc(awk_restlen(iterate, &sq, &dq) + 1, \
	sizeof(char));
	nullify_ints(&sq, &dq, &i);
	awk_filestr(&data, iterate, h);
	data.temp = ft_strjoin(data.to_split_options, " ");
	cmd_node->to_split = ft_strjoin(data.temp, data.to_split_options_rest);
	iterate = skip_awk(iterate, &sq, &dq);
	awk_free(&data);
	return (iterate);
}
// awk '/int/ { print $1 }' minishell30 .c "pipe.c" | grep i
// awk '/shell_info/ { print $1 }' minishell40 .c "pipe.c" | grep i
// awk '/shell_info/ { print $1 }' "minishel40 l.c" "pipe.c" | grep i
// '/int/ { print $1 }' minishell.c "pipe.c" | grep i