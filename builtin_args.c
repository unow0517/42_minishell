#include "minishell.h"

static void	nullify_ints(int *inside_sq, int *inside_dq, int *i, int *counter)
{
	*i = 0;
	*counter = 0;
	*inside_dq = 0;
	*inside_sq = 0;
}

char *arg_for_export(t_token *cur)
{
	int		i;
	int		counter;
	char	*arg;
	int		inside_sq; //if character is within quoted string set to 1
	int		inside_dq; //if character is within quoted string set to 1

	nullify_ints(&inside_sq, &inside_dq, &i, &counter);
	if (!cur)
		return (NULL);
	while (cur->content[i] != '\0')
	{
		update_quote_state(cur, &inside_sq, &inside_dq, i);
		if (is_redir_pipe(cur->content[i]) == true && inside_sq == 0 && inside_dq == 0)
			break;
		counter++;
	}
	nullify_ints(&inside_sq, &inside_dq, &i, &counter);
	arg = ft_calloc(counter + 1, sizeof(char));
	if (!arg)
		return (NULL);
	while (cur->content[i] != '\0')
	{
		update_quote_state(cur, &inside_sq, &inside_dq, i);
		if (is_redir_pipe_char(cur->content[i]) == true && inside_sq == 0 && inside_dq == 0)
			break;
		arg[i] = cur->content[i];
		i++;
	}
	return (arg);
}

void	update_quote_state(t_token *cur, int *inside_sq, int *inside_dq, int i)
{
	if (cur->content[i] == '\'' && *inside_sq == 0)
		*inside_sq = 1;
	else if (cur->content[i] == '\'' && *inside_sq == 1)
		*inside_sq = 0;
	if (cur->content[i] == '"' && *inside_dq == 0)
		*inside_dq = 1;
	else if (cur->content[i] == '"' && *inside_dq == 1)
		*inside_dq = 0;
}

t_token	*skip_tokens_of_builtin_arg(t_token *iterate)
{
	int		inside_sq;
	int		inside_dq;

	inside_dq = 0;
	inside_sq = 0;
	while (iterate)
	{
		update_quote_state_token(iterate, &inside_sq, &inside_dq);
		if (is_redir_pipe(iterate->token_type) == true && inside_sq == 0 && inside_dq == 0)
			return (iterate);
		iterate = iterate->next;
	}
	return (iterate);
}

void	update_quote_state_token(t_token *cur, int *inside_sq, int *inside_dq)
{
	if (cur->token_type == S_QUOTE && *inside_sq == 0)
		*inside_sq = 1;
	else if (cur->token_type == S_QUOTE && *inside_sq == 1)
		*inside_sq = 0;
	if (cur->token_type == D_QUOTE && *inside_dq == 0)
		*inside_dq = 1;
	else if (cur->token_type == D_QUOTE && *inside_dq == 1)
		*inside_dq = 0;
}

// char *arg_for_export(t_token *cur)
// {
// 	int	i;
// 	int	counter;
// 	char	*arg;
// 	int inside_sq; //if character is within quoted string set to 1
// 	int inside_dq; //if character is within quoted string set to 1
// 	i = 0;
// 	counter = 0;
// 	inside_dq = 0;
// 	inside_sq = 0;
// 	if (!cur)
// 		return (NULL);
// 	while (cur->content[i] != '\0' && is_redir_pipe(cur->content[i]) == false)
// 		counter++;
// 	i = 0;
// 	arg = ft_calloc(counter + 1, sizeof(char));
// 	if (!arg)
// 		return (NULL);
// 	while (cur->content[i] != '\0' && is_redir_pipe(cur->content[i]) == false)
// 	{
// 		if (cur->content[i] == '\'' || cur->content[i] == '"')

// 		arg[i] = cur->content[i];
// 		i++;
// 	}
// 	return (arg);
// }

// char *quoted_str(char *quoted_str, char flag, int i)
// {
// 	int		len;
// 	int		j;
// 	char	c;

// 	// i = 0;
// 	j = i;
// 	len = 0;
// 	while (quoted_str[j] != '\0' && (quoted_str[j] != c || j == 0))
// 		j++;
// 	j += 1;
// 	len = j - i;
// 	quoted_str = ft_calloc(len + 1, sizeof(char));
// 	if (!quoted_str)
// 		return(NULL);
// 	while (len > 0)
// 	{
// 		quoted_str[i] = quoted_str[i];
// 		i++;
// 		len--;
// 	}
// // printf("quoted_str = %s\n", quoted_str);
// 	return (quoted_str);
// }