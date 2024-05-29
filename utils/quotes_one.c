/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:53:16 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 21:41:42 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_quote_state_str(const char *str, int *sq, int *dq, int i)
{
	if (!str)
		return ;
	if (str[i] == '\0')
		return ;
	if (str[i] == '\'' && *sq == 0)
		*sq = 1;
	else if (str[i] == '\'' && *sq == 1)
		*sq = 0;
	if (str[i] == '"' && *dq == 0)
		*dq = 1;
	else if (str[i] == '"' && *dq == 1)
		*dq = 0;
}

t_token	*skip_q_tokens(t_token *iterate)
{
	t_token_type	hold_type;

	if (!iterate)
		return (NULL);
	hold_type = iterate->token_type;
	while (iterate && iterate->token_type == hold_type)
		iterate = iterate->next;
	return (iterate);
}

char	*rm_q_in_fullcmd(char *to_fix)
{
	char	*temp;
	char	c;

	temp = NULL;
	c = first_quote(to_fix);
	if (c != 'n')
	{
		temp = to_fix;
		to_fix = rm_quotes(temp, c);
		free(temp);
		temp = NULL;
	}
	return (to_fix);
}

void	quote_removal_in_exec_arg(t_command *cur_cmd)
{
	int		i;
	char	**to_fix;

	i = 0;
	while (cur_cmd)
	{
		if (cur_cmd->full_cmd)
		{
			to_fix = cur_cmd->full_cmd;
			while (to_fix && to_fix[i])
			{
				to_fix[i] = rm_q_in_fullcmd(to_fix[i]);
				i++;
			}
		}
		cur_cmd = cur_cmd->next;
	}
}

char	first_quote(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (str[i]);
		i++;
	}
	return ('n');
}
