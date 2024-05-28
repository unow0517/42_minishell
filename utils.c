/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:08:36 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/28 12:40:03 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_add_back(t_command **first_token, t_command *new)
{
	t_command	*end;

	if (!first_token || !new)
		return ;
	if (!*first_token)
	{
		*first_token = new;
		return ;
	}
	end = get_last_cmd(*first_token);
	end->next = new;
}

t_command	*get_last_cmd(t_command *cmd)
{
	if (!cmd)
		return (NULL);
	while (cmd && cmd->next)
		cmd = cmd->next;
	return (cmd);
}

void	token_add_back(t_token **first_token, t_token *new)
{
	t_token	*end;

	if (!first_token || !new)
		return ;
	if (!*first_token)
	{
		*first_token = new;
		return ;
	}
	end = token_last(*first_token);
	end->next = new;
}

t_token	*token_last(t_token *token)
{
	if (!token)
		return (NULL);
	while (token && token->next)
		token = token->next;
	return (token);
}


int	skip_whitespace(char *inpt, int i)
{
	while (inpt[i] != '\0' && (inpt[i] == ' ' || inpt[i] == '\t' || inpt[i] == '\r' ||\
	 inpt[i] == '\n' || inpt[i] == '\v' || inpt[i] == '\f'))
	 	i++;
	return (i);
}

bool	is_metacharacter(char c)
{
	if (c == '|' || c =='>' || c == '<' || c == '"' || c == '\'')
		return (true);
	return (false);
}

bool	is_metacharacter_type(int i)
{
	if (i == PIPE || i == S_QUOTE || i == D_QUOTE || i == S_LESS ||\
	 i == S_MORE || i == D_LESS || i == D_MORE)
		return (true);
	return (false);
}

bool	is_redir(int i)
{
	if (i == S_LESS || i == S_MORE || i == D_LESS || i == D_MORE)
		return (true);
	return (false);
}

bool	is_redir_pipe(t_token_type i)
{
	if (i == S_LESS || i == S_MORE || i == D_LESS || i == D_MORE || i == PIPE)
		return (true);
	return (false);
}

bool	is_redir_pipe_char(char i)
{
	if (i == '<' || i == '>' || i == '|')
		return (true);
	return (false);
}

bool	is_ws(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

int	num_of_remaining_cmds(t_command *cur) //check if needed
{
	int	counter;

	counter = 0;
	while (cur)
	{
		cur = cur->next;
		counter++;
	}
	return (counter);
}

int	num_of_total_cmds(t_command *cur)
{
	int	counter;

	counter = 0;
	while (cur)
	{
		cur = cur->next;
		counter++;
	}
	return (counter);
}

void	close_fds(t_shell *shell_info, t_command *cur)
{
	close_io(cur);
	if (shell_info->fd[0] != -1)
		close(shell_info->fd[0]);
	if (shell_info->fd[1] != -1)
		close(shell_info->fd[1]);
}

void	close_io(t_command *cur)
{
	if (cur->input_fd != -1)
		close(cur->input_fd);
	if (cur->output_fd != -1)
		close(cur->output_fd);
}

int	handle_exit(int status)
{
	int	exit_code;
	int	signal;

	if (WIFEXITED(status) == 1)
		exit_code =  WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		exit_code = signal + 128;
	}
	return (exit_code);
}

int	token_count(t_shell *shell_info)
{
	int	counter;
	t_token *iter;

	iter = shell_info->tokens;
	counter = 0;
	while (iter)
	{
		iter = iter->next;
		counter++;
	}
	return (counter);
}

bool	ft_is_builtin(char *str)
{
	if	(str)
	{
		if (ft_strncmp(str, "\"echo\"", 6) == 0 || ft_strncmp(str, "echo", 4) == 0)
			return (true);
		else if (ft_strncmp(str, "\"cd\"", 4) == 0 || ft_strncmp(str, "cd", 2) == 0)
			return (true);
		else if (ft_strncmp(str, "\"pwd\"", 5) == 0 || ft_strncmp(str, "pwd", 3) == 0)
			return (true);
		else if (ft_strncmp(str, "\"export\"", 8) == 0 || ft_strncmp(str, "export", 6) == 0)
			return (true);
		else if (ft_strncmp(str, "\"unset\"", 7) == 0 || ft_strncmp(str, "unset", 5) == 0)
			return (true);
		else if (ft_strncmp(str, "\"env\"", 5) == 0 || ft_strncmp(str, "env", 3) == 0)
			return (true);
		else if (ft_strncmp(str, "\"exit\"", 6) == 0 || ft_strncmp(str, "exit", 4) == 0)
			return (true);
		else if (ft_strncmp(str, "\"pwd\"", 5) == 0 || ft_strncmp(str, "pwd", 3) == 0)
			return (true);
		else if (ft_strncmp(str, "\"history\"", 9) == 0 || ft_strncmp(str, "history", 7) == 0)
			return (true);
	}
	return (false);
}
void	nullify_ints_four(int *inside_sq, int *inside_dq, int *i, int *counter)
{
	*i = 0;
	*counter = 0;
	*inside_dq = 0;
	*inside_sq = 0;
}

bool	quotes_even(char *input)
{
	int		i;
	int		q_counter;
	int		inside_sq;
	int		inside_dq;

	nullify_ints_four(&inside_sq, &inside_dq, &i, &q_counter);
	if (!input)
		return (true);
	while (input[i] != '\0')
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			if ((inside_dq + inside_sq) == 0 || \
			(inside_sq == 1 && input[i] == '\'') || \
			(inside_dq == 1 && input[i] == '"'))
			{
				update_quote_state_str(input, &inside_sq, &inside_dq, i);
				q_counter++;
			}
		}
		i++;
	}
	if (q_counter % 2 == 0)
		return (true);
	return (false);
}

char	*remove_unecessary_q(t_shell *shell_info)
{
	char	*temp;
	char	*new;
	int		counter;
	int		i;
	int		j;

	j = 0;
	i = 0;
	counter = 0;
	temp = shell_info->user_input;
	while (temp && temp[i] != '\0')
	{
		if (temp[i + 1] && ((temp[i] == '"' && temp[i + 1] == '"') || (temp[i] == '\'' && temp[i + 1] == '\'')))
			counter += 2;
		i++;
	}
	new = ft_calloc(i - counter + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (temp && temp[i] != '\0')
	{
		if (temp[i + 1] && ((temp[i] == '"' && temp[i + 1] == '"') || (temp[i] == '\'' && temp[i + 1] == '\'')))
			i += 2;
		if (temp[i])
		{
			new[j] = temp[i];
			i++;
		}
		j++;
	}
	free(temp);
	return (new);
}

bool	is_double(t_shell *shell_info, int i)
{
	if ((shell_info->user_input[i] == '>' && \
	shell_info->user_input[i + 1] == '>') || \
	(shell_info->user_input[i] == '<' && shell_info->user_input[i + 1] == '<'))
		return (true);
	return (false);
}

void	finalise_node(t_shell *shell_info, t_command *cmd_node)
{
	if (cmd_node->is_builtin == 0)
		init_cmds_in_struct(cmd_node, cmd_node->to_split);
	cmd_add_back(&shell_info->first_command, cmd_node);
	quote_removal_in_exec_arg(cmd_node);
}

void	reset(t_shell *shell_info)
{
	free_tokens(&shell_info->tokens);
	free_cmd_list(&shell_info->first_command);
	shell_info->syntax_error = false;
}

bool	has_double_pipe(t_token *iter, int dq, int sq)
{
	if (iter->token_type == PIPE && iter->next && \
	iter->next->token_type == PIPE && dq == 0 && sq == 0)
		return (true);
	return (false);
}

t_token	*double_pipe_case(t_shell *shell_info, t_token *iter)
{
	if (shell_info->tokens->token_type == WORD)
		unexpected_token(shell_info, get_first_word(shell_info->tokens->content));
	else
		unexpected_token(shell_info, "|");
	while (iter && iter->token_type == PIPE)
		iter = iter->next;
	return (iter);
}

bool	has_redir_twice(t_token *iter, int dq, int sq)
{
	if (is_redir(iter->token_type) && \
	is_redir(iter->next->token_type) && dq == 0 && sq == 0)
		return (true);
	return (false);
}

t_token	*twice_redir_case(t_shell *shell_info, t_token *iter)
{
	if ((iter->token_type == S_MORE && iter->next->token_type == S_LESS) || \
	(iter->token_type == S_LESS && iter->next->token_type == S_MORE))
		unexpected_token(shell_info, "<>");
	else if (iter->next->token_type == D_LESS || \
	iter->next->token_type == S_LESS)
		unexpected_token(shell_info, "<");
	else if (iter->next->token_type == D_MORE || \
	iter->next->token_type == S_MORE)
		unexpected_token(shell_info, ">");
	while (iter && is_redir(iter->token_type))
		iter = iter->next;
	return (iter);
}

bool	syntax_error_at_start(t_token *iter)
{
	if ((iter->token_type == PIPE && !iter->next) || \
	(iter->token_type == PIPE && iter->next->token_type != PIPE))
		return (true);
	else if (iter->token_type == PIPE && iter->next && \
	iter->next->token_type == PIPE)
		return (true);
	else if (is_redir(iter->token_type) == true && !iter->next)
		return (true);
	return (false);
}

void	syntax_error_at_start_msg(t_shell *shell_info, t_token *iter)
{
	if ((iter->token_type == PIPE && !iter->next) || \
	(iter->token_type == PIPE && iter->next->token_type != PIPE))
		unexpected_token(shell_info, "|");
	else if (iter->token_type == PIPE && iter->next && \
	iter->next->token_type == PIPE)
		unexpected_token(shell_info, "|");
	else if (is_redir(iter->token_type) == true && !iter->next)
		unexpected_token(shell_info, "newline");
}
