#include "minishell.h"

static t_token	*initialize_cmd_helper(t_token *iterate, t_command *cmd_node, \
t_token_type flag)
{
	char	*temp_cmd;
	char	c;

	c = 0;
	if (flag == D_QUOTE)
		c = '"';
	else if (flag == S_QUOTE)
		c = '\'';
	temp_cmd = quote_handler(iterate, flag);
	cmd_node->cmd = rm_quotes(temp_cmd, c);
	free(temp_cmd);
	iterate = skip_quoted_str(iterate, flag);
	return (iterate);
}

t_token	*initialize_cmd(t_token *iterate, t_command *cmd_node)
{
	char	*first_word;

	first_word = get_first_word(iterate->content);
	if (first_word && ft_strncmp("awk", first_word, 3) == 0)
		iterate = handle_awk(iterate, cmd_node);
	else if (first_word && iterate->token_type == WORD)
	{
		cmd_node->cmd = get_first_word(iterate->content);
		iterate = iterate->next;
	}
	else if (iterate->token_type == D_QUOTE)
		iterate = initialize_cmd_helper(iterate, cmd_node, D_QUOTE);
	else if (iterate->token_type == S_QUOTE)
		iterate = initialize_cmd_helper(iterate, cmd_node, S_QUOTE);
	if (first_word)
		free(first_word);
	return (iterate);
}

static t_token	*initialize_cmd_options_helper(t_token *iterate, \
t_command *cmd_node, t_token_type flag)
{
	char	*quoted_str;
	char	*temp;
	char	*temp1;

	quoted_str = quote_handler(iterate, flag);
	temp = ft_strjoin(cmd_node->to_split, " ");
	temp1 = quoted_str;
	cmd_node->to_split = ft_strjoin(temp, temp1);
	free(temp);
	iterate = skip_quoted_str(iterate, flag);
	return (iterate);
}

t_token	*initialize_cmd_options(t_token *iterate, t_command *cmd_node)
{
	char	*temp;
	char	*temp1;

	if (iterate->token_type == D_QUOTE)
		iterate = initialize_cmd_options_helper(iterate, cmd_node, D_QUOTE);
	else if (iterate->token_type == S_QUOTE)
		iterate = initialize_cmd_options_helper(iterate, cmd_node, S_QUOTE);
	else
	{
		temp = ft_strjoin(cmd_node->to_split, " ");
		temp1 = get_first_word(iterate->content);
		cmd_node->to_split = ft_strjoin(temp, get_first_word(iterate->content));
		cmd_node->to_split = ft_strjoin(temp, temp1);
		free(temp);
		free(temp1);
		iterate = iterate->next;
	}
	return (iterate);
}
