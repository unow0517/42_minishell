#include "minishell.h"

bool	builtin_case(t_token *iterate)
{
	char	*word;

	word = get_first_word(iterate->content);
	if (iterate && (ft_is_builtin(word) == true \
	|| ft_is_builtin(iterate->content) == true))
	{
		free(word);
		return (true);
	}
	if (word)
		free(word);
	return (false);
}

bool	empty_cmd_case(t_token *iterate, t_command *cmd_node)
{
	if (iterate && (iterate->token_type == WORD || \
	iterate->token_type == D_QUOTE \
	|| iterate->token_type == S_QUOTE) && (cmd_node->cmd == NULL) && \
	iterate->token_type != PIPE)
		return (true);
	return (false);
}

bool	full_cmd_case(t_token *iterate, t_command *cmd_node)
{
	if (iterate && (iterate->token_type == WORD \
	|| iterate->token_type == D_QUOTE || iterate->token_type == S_QUOTE) \
	&& cmd_node->cmd != NULL && \
	iterate->token_type != PIPE)
		return (true);
	return (false);
}
