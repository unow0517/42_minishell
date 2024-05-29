/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_ms.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:53:41 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 11:55:57 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*substrings(char const *s, char c, char **array);

static char	**freeing(char **array, int i);

static int	ft_count(char const *s, char c)
{
	int		i;
	int		count;
	int		sq;
	int		dq;

	dq = 0;
	sq = 0;
	i = 0;
	count = 0;
	while (s && s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
		{
			update_quote_state_str(s, &sq, &dq, i);
			i++;
		}
		if ((s[i] != '\0' && s[i] != c) && dq == 0 && sq == 0)
			count++;
		while (s[i] != '\0' && s[i] != c)
		{
			update_quote_state_str(s, &sq, &dq, i);
			i++;
		}
	}
	return (count);
}

char	**split_ms(char const *s, char c)
{
	char	**array;

	array = (char **)ft_calloc(ft_count(s, c) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	substrings(s, c, array);
	return (array);
}

void	free_arr(char **array, int i)
{
	if (!array[i])
		freeing(array, i);
}

static char	*substrings(char const *s, char c, char **array)
{
	int		i;
	int		start;
	int		end;
	int		sq;
	int		dq;

	nullify_ints_four(&sq, &dq, &i, &start);
	while (ft_count(s, c) > i)
	{
		update_position(&end, &start, s, c);
		while (s[end] != '\0')
		{
			if (s[end] == c && sq == 0 && dq == 0)
				break ;
			update_ints(s, &end, &dq, &sq);
			if (sq == 0 && dq == 0 && s[end] == c)
				break ;
			if (s[end] && s[end] != '"' && s[end] != '\'')
				end++;
		}
		array[i] = create_ms_split_array(array[i], &end, &start, s);
		free_arr(array, i);
		i++;
	}
	return (array[i]);
}

static char	**freeing(char **array, int i)
{
	while (array[i > 0])
	{
		i--;
		free(array[i - 1]);
	}
	free(array);
	return (NULL);
}
