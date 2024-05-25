#include "minishell.h"

static void	arg_counter(t_token *cur, int *sq, int *dq, int *counter)
{
	int	i;

	i = 0;
	while (cur->content[i] != '\0')
	{
		update_quote_state(cur, sq, dq, i);
		if (is_redir_pipe(cur->content[i]) == true && sq == 0 && dq == 0)
			break ;
		*counter = *counter + 1;
		i++;
	}
}

static void	nullify_ints_two(int *inside_sq, int *inside_dq)
{
	*inside_dq = 0;
	*inside_sq = 0;
}

char	*arg_for_export(t_token *cur)
{
	int		i;
	int		counter;
	char	*arg;
	int		inside_sq;
	int		inside_dq;

	nullify_ints_four(&inside_sq, &inside_dq, &i, &counter);
	if (!cur)
		return (NULL);
	arg_counter(cur, &inside_sq, &inside_dq, &counter);
	nullify_ints_two(&inside_sq, &inside_dq);
	arg = ft_calloc(counter + 1, sizeof(char));
	if (!arg)
		return (NULL);
	while (cur->content[i] != '\0')
	{
		update_quote_state(cur, &inside_sq, &inside_dq, i);
		if (is_redir_pipe_char(cur->content[i]) == true && \
		inside_sq == 0 && inside_dq == 0)
			break ;
		if (cur->content[i])
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
	int	inside_sq;
	int	inside_dq;

	inside_dq = 0;
	inside_sq = 0;
	while (iterate != NULL)
	{
		if ((inside_sq == 1 && iterate->content[0] == '\'') || \
		(inside_dq == 1 && iterate->content[0] == '"'))
			update_quote_state_token(iterate, &inside_sq, &inside_dq);
		if (is_redir_pipe(iterate->token_type) == true && \
		inside_sq == 0 && inside_dq == 0)
			break ;
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

t_token	*initialise_builtin_type_arg(t_command *cmd_node, t_token *iterate)
{
	if (iterate->token_type == WORD)
		cmd_node->builtin_type = get_first_word(iterate->content);
	else if (iterate->token_type == S_QUOTE || iterate->token_type == D_QUOTE)
		cmd_node->builtin_type = get_first_word(iterate->next->content);
	cmd_node->is_builtin = true;
	if (iterate && (iterate->token_type == S_QUOTE || \
	iterate->token_type == D_QUOTE) && iterate->next->next->next)
		cmd_node->builtin_arg = arg_for_export(iterate->next->next->next);
	else if (iterate && iterate->next)
		cmd_node->builtin_arg = arg_for_export(iterate->next);
	iterate = skip_tokens_of_builtin_arg(iterate);
	return (iterate);
}
