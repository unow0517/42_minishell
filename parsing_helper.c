#include "minishell.h"

static t_token	*initialize_cmd_helper(t_token *iterate, t_command *cmd_node, t_token_type flag)
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

static t_token	*initialize_cmd_options_helper(t_token *iterate, t_command *cmd_node, t_token_type flag)
{
	char	*quoted_str;
	char	*temp;
	char	*temp1;

	quoted_str = quote_handler(iterate, flag);
	temp = ft_strjoin(cmd_node->to_split, " ");
	temp1 = quoted_str; //-l
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
		temp1 = get_first_word(iterate->content); //-l
		cmd_node->to_split = ft_strjoin(temp, get_first_word(iterate->content));
		cmd_node->to_split = ft_strjoin(temp, temp1);
		free(temp);
		free(temp1);
		iterate = iterate->next;
	}
	return (iterate);
}

static char *rm_q_in_fullcmd(char *to_fix)
{
	char	*temp;
	char	c;

	temp = NULL;
	c = first_quote(to_fix);
	if (c != 'n')
	{
		temp = ft_calloc(ft_strlen(to_fix), sizeof(char));
		if (!temp)
			return (NULL);
		temp = to_fix;
		to_fix = rm_quotes(temp, c);
		free(temp);
	}
	return (to_fix);
}

void	quote_removal_in_exec_arg(t_command *cur_cmd)
{
	int		i;
	char	**to_fix;

	i = 0;
	while (cur_cmd)
	{
		if (cur_cmd->full_cmd)
		{
			to_fix = cur_cmd->full_cmd;
			while (to_fix && to_fix[i])
			{
				to_fix[i] = rm_q_in_fullcmd(to_fix[i]);
				i++;
			}
		}
		cur_cmd = cur_cmd->next;
	}
}

char	first_quote(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (str[i]);
		i++;
	}
	return ('n');
}

static int	count_quotes(char *to_fix, char c, int *q_counter, int *i);
static char	*outer_q_removed_str(char *to_fix, char c, char *new);


char	*rm_quotes(char *to_fix, char c)
{
	int		i;
	int		j;
	int		q_counter;
	char	*new;

	i = 0;
	j = 0;
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
	int i;
	int j;

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


t_token	*skip_q_tokens(t_token *iterate)
{
	t_token_type	hold_type;

	if (!iterate)
		return (NULL);
	hold_type = iterate->token_type;
	while (iterate && iterate->token_type == hold_type)
		iterate = iterate->next;
	return (iterate);
}
