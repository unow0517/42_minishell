/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:51:03 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 11:56:26 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_ms_split_array(char *array, int *end, int *start, char const *s)
{
	array = ft_substr(s, *start, (*end - (*start)));
	*start = *end;
	return (array);
}

void	update_ints(char const *s, int *end, int *dq, int*sq)
{
	if (s[*end] == '"' || s[*end] == '\'')
	{
		if (s[*end] == '"' || s[*end] == '\'')
			update_quote_state_str(s, sq, dq, *end);
		(*end)++;
	}
}

void	update_position(int *end, int *start, char const *s, char c)
{
	while (s[*start] == c)
		(*start)++;
	*end = *start;
}
