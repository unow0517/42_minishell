#include "minishell.h"

t_token *initialize_cmd(t_shell *shell_info, t_token *iterate, t_command *cmd_node)
{
	char	*quoted_str;
	char *temp_cmd;
	quoted_str = NULL;
	if (ft_strncmp("awk", get_first_word(iterate->content), 3) == 0)
		iterate = handle_awk(shell_info, iterate, cmd_node);
	else if (iterate->token_type == WORD)
	{
		cmd_node->cmd = get_first_word(iterate->content);
		iterate = iterate->next;
	}
	else if (iterate->token_type == D_QUOTE)
	{
		temp_cmd = quote_handler(shell_info, iterate, quoted_str, D_QUOTE);
		cmd_node->cmd = rm_quotes(temp_cmd, '"');
		free(temp_cmd);
		iterate = skip_quoted_str(iterate, D_QUOTE);
	}
	else if (iterate->token_type == S_QUOTE)
	{
		temp_cmd = quote_handler(shell_info, iterate, quoted_str, S_QUOTE);
		cmd_node->cmd = rm_quotes(temp_cmd, '\'');
		free(temp_cmd);
		iterate = skip_quoted_str(iterate, S_QUOTE);
	}
	return (iterate);
}

static void	nullify_ints(int *inside_sq, int *inside_dq, int *i)
{
	*i = 0;
	*inside_dq = 0;
	*inside_sq = 0;
}

t_token	*handle_awk(t_shell *shell_info, t_token *iterate, t_command *cmd_node)
{
	int		i;
	int		j;
	int		inside_sq;
	int		inside_dq;
	char	*to_split_options;
	char	*to_split_options_rest;
	char	*to_split_options_total;

	(void)shell_info;
	nullify_ints(&inside_sq, &inside_dq, &i);
	cmd_node->cmd = get_first_word(iterate->content);
	iterate = iterate->next;
	while (iterate->content[i] != '\0' && (iterate->content[i] != '\'' || i == 0)) //LENGTH OF 'single_quoted_part' PART
		i++;
	to_split_options = ft_calloc(i + 1, sizeof(char));
	i = 0;
	while (iterate->content[i] != '\0' && (iterate->content[i] != '\'' || i == 0)) //CREATE 'single_quoted_part' STRING
	{
		to_split_options[i] = iterate->content[i];
		i++;
	}
	nullify_ints(&inside_sq, &inside_dq, &j);
	int h = i;
	while (iterate->content[i] != '\0') //LENGTH OF FILES
	{
		update_quote_state(iterate, &inside_sq, &inside_dq, i);
		if (is_redir_pipe(iterate->content[h]) == true && inside_sq == 0 && inside_dq == 0)
			break;
		i++;
		j++;
	}
	to_split_options_rest = ft_calloc(j + 1, sizeof(char));
	nullify_ints(&inside_sq, &inside_dq, &i);
	while (iterate->content[h] != '\0') //CREATE FILE STRING // && is_redir_pipe(iterate->content[h]) == false
	{
		update_quote_state(iterate, &inside_sq, &inside_dq, i);
		if (is_redir_pipe(iterate->content[h]) == true && inside_sq == 0 && inside_dq == 0)
			break;
		to_split_options_rest[i] = iterate->content[h];
		i++;
		h++;
	}
	char *temp;
	temp = ft_strjoin(to_split_options, " ");
	to_split_options_total = ft_strjoin(temp, to_split_options_rest); //JOIN STRINGS TO CREATE OPTIONS
	cmd_node->to_split = to_split_options_total;
	nullify_ints(&inside_sq, &inside_dq, &i);
	while (iterate)
	{
		update_quote_state_token(iterate, &inside_sq, &inside_dq);
		if(is_redir_pipe(iterate->token_type) == true && inside_dq == 0 && inside_sq == 0 && i != 0)
			break;
		iterate = iterate->next;
	}
	return (iterate);
}

t_token	*initialize_cmd_options(t_shell *shell_info, t_token *iterate, t_command *cmd_node)
{
	char	*quoted_str;
	char	*temp;
	char	*temp1;

	quoted_str = NULL;
	if (iterate->token_type == D_QUOTE)
	{
		quoted_str = quote_handler(shell_info, iterate, quoted_str, D_QUOTE);
		temp = ft_strjoin(cmd_node->to_split, " ");
		temp1 = quoted_str; //-l
		cmd_node->to_split = ft_strjoin(temp, temp1);
		free(temp);
		// free(temp1);
		iterate = skip_quoted_str(iterate, D_QUOTE);
	}
	else if (iterate->token_type == S_QUOTE)
	{
		// iterate = iterate->next;
		quoted_str = quote_handler(shell_info, iterate, quoted_str, S_QUOTE);
		temp = ft_strjoin(cmd_node->to_split, " ");
		temp1 = quoted_str; //-l							//remove
		cmd_node->to_split = ft_strjoin(temp, quoted_str);
		cmd_node->to_split = ft_strjoin(temp, temp1);
		free(temp);
		// free(temp1);
		iterate = skip_quoted_str(iterate, S_QUOTE);
	}
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

void	quote_removal_in_exec_arg(t_command *cur_cmd)
{
	int			i;
	int			j;
	char		**to_fix;
	char		*temp;
	char		c;

	i = 0;
	j = 0;
	while (cur_cmd)
	{
		if (cur_cmd->full_cmd)
		{
			to_fix = cur_cmd->full_cmd;
			while (to_fix && to_fix[i])
			{
				c = first_quote(to_fix[i]);
				if (c != 'n')
				{
					temp = ft_calloc(ft_strlen(to_fix[i]), sizeof(char));
					if (!temp)
						return ;
					temp = to_fix[i];
					to_fix[i] = rm_quotes(temp, c);
					free(temp);
				}
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
	while (to_fix && to_fix[i] != '\0')
	{
		if (to_fix[i] == c)
			q_counter++;
		i++;
	}
	new = ft_calloc(i - q_counter + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (to_fix && to_fix[i])
	{
		if (to_fix[i] == c)
			i++;
		if (to_fix[i] != '\0' && to_fix[i] != c)
		{
			new[j] = to_fix[i];
			j++;
		}
		i++;
// free(to_fix);
	}
	if (new && new[0] == '\0')
		return (NULL);
	return (new);
}

t_token	*skip_q_tokens(t_token *iterate)
{
	t_token_type hold_type;

	if (!iterate)
		return (NULL);
	hold_type = iterate->token_type;
	while (iterate && iterate->token_type == hold_type)
		iterate = iterate->next;
	return (iterate);
}
