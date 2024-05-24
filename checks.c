/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:39:36 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/24 14:27:25 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	ft_printf("current token = %p\n", token);
	ft_printf("token->input = %s\n", token->input);
	ft_printf("token->len = %i\n", token->len);
	ft_printf("token->idx = %i\n", token->idx);
	ft_printf("token->content = %s\n", &token->input[token->idx]);
	ft_printf("token->token_type = %i\n", token->token_type);
	ft_printf("token->next = %p\n", token->next);
}

void	print_linked_tokens(t_token *token)
{
	while (token)
	{
		ft_printf("________________________________________________________\n");
		print_token(token);
		token = token->next;
	}
}

void	print_split(char **str)
{
	int i = 0;

	while (str[i])
	{
		printf("str[%i] = %s\n", i, str[i]);
		i++;
	}
}

void	print_split_no_newline(char **str)
{
	int i = 0;

	while (str[i])
	{
		printf("\t\t\tstr[%i] = %s\n", i, str[i]);
		i++;
	}
}


void	print_cmd_list(t_command *cmd_node)
{
	while (cmd_node)
	{
		printf("________________________________________________________\n");
		printf("cmd_node\t\t%p\n", cmd_node);
		if (cmd_node->cmd)
			printf("cmd_node->cmd\t\t%s\n", cmd_node->cmd);
		printf("cmd_node->options\n");
		if (cmd_node->options)
			print_split_no_newline(cmd_node->options);
		printf("cmd_node->full_cmd\n");
		if (cmd_node->full_cmd)
			print_split_no_newline(cmd_node->full_cmd);
		printf("cmd_node->input_fd\t%i\n", cmd_node->input_fd);
		printf("cmd_node->output_fd\t%i\n", cmd_node->output_fd);
		// printf("cmd_node->output_path\t%s\n", cmd_node->output_path);
		// printf("cmd_node->input_path\t%s\n", cmd_node->input_path);
		printf("cmd_node->is_heredoc\t%i\n", cmd_node->is_heredoc);
		printf("cmd_node->file_not_found\t%i\n", cmd_node->file_not_found);
		printf("cmd_node->filename\t%s\n", cmd_node->filename);
		printf("cmd_node->is_builtin\t%i\n", cmd_node->is_builtin);
		printf("cmd_node->builtin_type\t%s\n", cmd_node->builtin_type);
		printf("cmd_node->builtin_arg\t%s\n", cmd_node->builtin_arg);
		printf("cmd_node->to_split\t%s\n", cmd_node->to_split);
		printf("cmd_node->next\t%p\n", cmd_node->next);
		cmd_node = cmd_node->next;
	}
}

void	print_token_types(t_shell *shell_info)
{
	t_token *token;

	token = shell_info->tokens;
	while (token)
	{
		printf("\t");
		if (token->token_type == 0)
			printf("NO_TOKEN");
		else if (token->token_type == 1)
			printf("WORD");
		else if (token->token_type == 2)
			printf("PIPE");
		else if (token->token_type == 3)
			printf("S_QUOTE");
		else if (token->token_type == 4)
			printf("D_QUOTE");
		else if (token->token_type == 5)
			printf("S_LESS");
		else if (token->token_type == 6)
			printf("S_MORE");
		else if (token->token_type == 7)
			printf("D_LESS");
		else if (token->token_type == 8)
			printf("D_MORE");
		token = token->next;
	}
	printf("\n");
}

void	syntax_error_check(t_shell *shell_info)
{
	t_token	*iter;
	int		inside_dq;
	int		inside_sq;

	inside_dq = 0;
	inside_sq = 0;
	if (!shell_info->tokens)
		return ;
	iter = shell_info->tokens;
	if ((iter->token_type == PIPE && !iter->next) || (iter->token_type == PIPE && iter->next->token_type != PIPE))
		unexpected_token(shell_info, "|"); // bash: syntax error near unexpected token `|';
	else if (iter->token_type == PIPE && iter->next && iter->next->token_type == PIPE)
		unexpected_token(shell_info, "||");
	else if (is_redir(iter->token_type) == true && !iter->next)
		unexpected_token(shell_info, "newline");
	else
	{
		while (iter && iter->next)
		{
			update_quote_state(iter, &inside_sq, &inside_dq, 0);
			if (is_redir(iter->token_type) && is_redir(iter->next->token_type) && inside_dq == 0 && inside_sq == 0)
			{
				if ((iter->token_type == S_MORE && iter->next->token_type == S_LESS) || (iter->token_type == S_LESS && iter->next->token_type == S_MORE))
					unexpected_token(shell_info, "<>");
				else if (iter->next->token_type == D_LESS || iter->next->token_type == S_LESS)
					unexpected_token(shell_info, "<");
				else if (iter->next->token_type == D_MORE || iter->next->token_type == S_MORE)
					unexpected_token(shell_info, ">");
				while (iter && is_redir(iter->token_type))
					iter = iter->next;
			}
			else if (iter->token_type == PIPE && iter->next && iter->next->token_type == PIPE && inside_dq == 0 && inside_sq == 0)
			{
				if (shell_info->tokens->token_type == WORD)
					unexpected_token(shell_info, get_first_word(shell_info->tokens->content));
				else
					unexpected_token(shell_info, "|");
				while (iter && iter->token_type == PIPE)
					iter = iter->next;
			}
			if (iter)
				iter = iter->next;
		}
	}
}

// bash: syntax error near unexpected token `newline'
// bash-3.2$ < out < out |
// > 
// > <
// bash: syntax error near unexpected token `newline'
// bash-3.2$ |
// bash: syntax error near unexpected token `|'
// bash-3.2$ ls |
// > |
// bash: syntax error near unexpected token `|'
// bash-3.2$ |
// bash: syntax error near unexpected token `|'
// bash-3.2$ |||||
// bash: syntax error near unexpected token `||'
// bash-3.2$ ||||||||||||
// bash: syntax error near unexpected token `||'
// bash-3.2$ |||||||||
// bash: syntax error near unexpected token `||'
// bash-3.2$ | ls
// bash: syntax error near unexpected token `|'