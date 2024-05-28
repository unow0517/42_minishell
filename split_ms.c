#include "minishell.h"

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

void	update_quote_state_str(const char *str, int *sq, \
int *dq, int i)
{
	if (str[i] == '\'' && *sq == 0)
		*sq = 1;
	else if (str[i] == '\'' && *sq == 1)
		*sq = 0;
	if (str[i] == '"' && *dq == 0)
		*dq = 1;
	else if (str[i] == '"' && *dq == 1)
		*dq = 0;
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
		// array[i] = ft_substr(s, start, (end - start));
		// start = end;
		if (!array[i])
			freeing(array, i);
		i++;
	}
	return (array[i]);
}

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
