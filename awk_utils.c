#include "minishell.h"

int	awk_sqlen(t_token *iterate)
{
	int	i;

	i = 0;
	while (iterate->content[i] != '\0' && \
	(iterate->content[i] != '\'' || i == 0))
		i++;
	return (i);
}

int	awk_restlen(t_token *iterate, int *sq, int *dq)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (iterate->content[i] != '\0')
	{
		if (iterate->content[i] == '\'' || iterate->content[i] == '"')
			update_quote_state_str(&iterate->content[i], sq, dq, i);
		if (is_redir_pipe_char(iterate->content[i]) == true && sq == 0 && \
		dq == 0)
			break ;
		i++;
		j++;
	}
	return (j);
}

int	awk_sq_part(t_awk_data *data, t_token *iterate)
{
	int	i;

	i = 0;
	while (iterate->content[i] != '\0' && \
	(iterate->content[i] != '\'' || i == 0))
	{
		data->to_split_options[i] = iterate->content[i];
		i++;
	}
	data->to_split_options[i] = iterate->content[i];
	i++;
	return (i);
}

void	awk_filestr(t_awk_data *data, t_token *iterate, int h)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (iterate->content[h] != '\0')
	{
		if (iterate->content[h] == '\'' || iterate->content[h] == '"')
			update_quote_state_str(&iterate->content[h], &sq, &dq, i);
		if (is_redir_pipe_char(iterate->content[h]) == true && sq == 0 && \
		dq == 0)
			break ;
		data->to_split_options_rest[i] = iterate->content[h];
		i++;
		h++;
	}
}

t_token	*skip_awk(t_token *iterate, int *sq, int *dq)
{
	while (iterate)
	{
		update_quote_state_token(iterate, sq, dq);
		if (is_redir_pipe(iterate->token_type) == true && *dq == 0 && *sq == 0)
			break ;
		iterate = iterate->next;
	}
	return (iterate);
}
