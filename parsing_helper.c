#include "minishell.h"

t_token *initialize_cmd(t_shell *shell_info, t_token *iterate, t_command *cmd_node)
{
	char	*quoted_str;
	char *temp_cmd;
	quoted_str = NULL;
	if (iterate->token_type == WORD)
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
		temp1 = quoted_str; //-l
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
