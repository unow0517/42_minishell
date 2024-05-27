/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:39:36 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/27 15:58:16 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	printf("current token = %p\n", token);
	printf("token->input = %s\n", token->input);
	printf("token->len = %i\n", token->len);
	printf("token->idx = %i\n", token->idx);
	printf("token->content = %s\n", &token->input[token->idx]);
	printf("token->token_type = %i\n", token->token_type);
	printf("token->next = %p\n", token->next);
}

void	print_linked_tokens(t_token *token)
{
	while (token)
	{
		printf("________________________________________________________\n");
		print_token(token);
		token = token->next;
	}
}

void	print_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		printf("str[%i] = %s\n", i, str[i]);
		i++;
	}
}

void	print_split_no_newline(char **str)
{
	int i;

	i = 0;
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
		printf("\n______________________________________________________\n");
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
		printf("cmd_node->is_heredoc\t%i\n", cmd_node->is_heredoc);
		printf("cmd_node->file_not_found\t%i\n", cmd_node->file_not_found);
		printf("cmd_node->filename\t%s\n", cmd_node->filename);
		printf("cmd_node->is_builtin\t%i\n", cmd_node->is_builtin);
		printf("cmd_node->builtin_type\t%s\n", cmd_node->builtin_type);
		printf("cmd_node->builtin_arg\t%s\n", cmd_node->builtin_arg);
		printf("cmd_node->to_split\t%s\n", cmd_node->to_split);
		printf("cmd_node->next\t%p\n\n\n", cmd_node->next);
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
		if (token->token_type == 1)
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
	int		dq;
	int		sq;

	dq = 0;
	sq = 0;
	if (!shell_info->tokens)
		return ;
	iter = shell_info->tokens;
	if (syntax_error_at_start(iter) == true)
		syntax_error_at_start_msg(shell_info, iter);
	else
	{
		while (iter && iter->next)
		{
			update_quote_state(iter, &sq, &dq, 0);
			if (has_redir_twice(iter, dq, sq) == true)
				iter = twice_redir_case(shell_info, iter);
			else if (has_double_pipe(iter, dq, sq) == true)
				iter = double_pipe_case(shell_info, iter);
			if (iter)
				iter = iter->next;
		}
	}
}
