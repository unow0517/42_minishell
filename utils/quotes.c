/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:53:09 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/30 17:50:05 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quote_handler(t_token *iterate, t_token_type flag)
{
	int		len;
	int		i;
	char	c;
	char	*quoted_str;

	if (flag == D_QUOTE)
		c = '"';
	else if (flag == S_QUOTE)
		c = '\'';
	i = 0;
	len = 0;
	while (iterate->content[len] != '\0' && \
	(iterate->content[len] != c || len == 0))
		len++;
	len += 1;
	quoted_str = ft_calloc(len + 1, sizeof(char));
	if (!quoted_str)
		return (NULL);
	while (len > 0)
	{
		quoted_str[i] = iterate->content[i];
		i++;
		len--;
	}
	return (quoted_str);
}

t_token	*skip_quoted_str(t_token *to_skip, t_token_type flag)
{
	to_skip = to_skip->next;
	while (to_skip && to_skip->token_type != flag)
		to_skip = to_skip->next;
	if (to_skip)
		to_skip = to_skip->next;
	return (to_skip);
}

static int	count_quotes(char *to_fix, char c, int *q_counter, int *i);
static char	*outer_q_removed_str(char *to_fix, char c, char *new);

char	*rm_quotes(char *to_fix, char c)
{
	int		i;
	int		q_counter;
	char	*new;

	i = 0;
	q_counter = 0;
	if (!to_fix)
		return (NULL);
	count_quotes(to_fix, c, &q_counter, &i);
	new = ft_calloc(i - q_counter + 1, sizeof(char));
	if (!new)
		return (NULL);
	new = outer_q_removed_str(to_fix, c, new);
	return (new);
}

static char	*outer_q_removed_str(char *to_fix, char c, char *new)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (to_fix && to_fix[i])
	{
		if (to_fix[i] != '\0' && to_fix[i] != c)
		{
			new[j] = to_fix[i];
			j++;
		}
		i++;
	}
	new[i] = '\0';
	return (new);
}

static int	count_quotes(char *to_fix, char c, int *q_counter, int *i)
{
	while (to_fix && to_fix[*i] != '\0')
	{
		if (to_fix[*i] == c)
			q_counter++;
		(*i)++;
	}
	return (*i);
}
