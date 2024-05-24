#include "minishell.h"

static char	*substrings(char const *s, char c, char **array);

static char	**freeing(char **array, int i);

static int	ft_count(char const *s, char c)
{
	int		i;
	int		count;
	int		inside_sq;
	int		inside_dq;

	inside_dq = 0;
	inside_sq = 0;
	i = 0;
	count = 0;
	while (s && s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
		{
			update_quote_state_str(s, &inside_sq, &inside_dq, i);
			i++;
		}
		if ((s[i] != '\0' && s[i] != c) && inside_dq == 0 && inside_sq == 0)
			count++;
		while (s[i] != '\0' && s[i] != c)
		{
			update_quote_state_str(s, &inside_sq, &inside_dq, i);
			i++;
		}
	}
	return (count);
}

// Allocates (with malloc(3)) and returns an array of strings obtained by
// splitting ’s’ using the character ’c’ as a delimiter. The array must end
// with a NULL pointer.
char	**split_ms(char const *s, char c)
{
	char	**array;

	array = (char **)ft_calloc(ft_count(s, c) + 1, sizeof(char *));
	if (!array)
		return (NULL);
	substrings(s, c, array);
	return (array);
}

void	update_quote_state_str(const char *str, int *inside_sq, int *inside_dq, int i)
{
	if (str[i] == '\'' && *inside_sq == 0)
		*inside_sq = 1;
	else if (str[i] == '\'' && *inside_sq == 1)
		*inside_sq = 0;
	if (str[i] == '"' && *inside_dq == 0)
		*inside_dq = 1;
	else if (str[i] == '"' && *inside_dq == 1)
		*inside_dq = 0;
}

static char	*substrings(char const *s, char c, char **array)
{
	int		i;
	int		start;
	int		end;
	int		inside_sq;
	int		inside_dq;

	inside_dq = 0;
	inside_sq = 0;
	i = 0;
	start = 0;
	while (ft_count(s, c) > i)
	{
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] != '\0')
		{
			if (s[end] == c && inside_sq == 0 && inside_dq == 0)
				break;
			if (s[end] == '"' || s[end] == '\'')
			{
				if (s[end] == '"' || s[end] == '\'')
					update_quote_state_str(s, &inside_sq, &inside_dq, end);
				end++;
			}
			if (inside_sq == 0 && inside_dq == 0 && s[end] == c)
				break;
			if (s[end] && s[end] != '"' && s[end] != '\'')
				end++;
		}
		array[i] = ft_substr(s, start, (end - start));
		if (!array[i])
			freeing(array, i);
		start = end;
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