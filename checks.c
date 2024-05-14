/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:39:36 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/09 17:07:38 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token(t_token *token)
{
	ft_printf("current token = %p\n", token);
	ft_printf("token->input = %s\n", token->input);
	ft_printf("token->len = %i\n", token->len);
	ft_printf("token->idx = %i\n", token->idx);
	// ft_printf("token->user_input_element = %s\n", token->user_input_element);
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
		printf("cmd_node->cmd\t\t%s\n", cmd_node->cmd);
		printf("cmd_node->options\n");
		print_split_no_newline(cmd_node->options);
		printf("cmd_node->full_cmd\n");
		print_split_no_newline(cmd_node->full_cmd);
		printf("cmd_node->input_fd\t%i\n", cmd_node->input_fd);
		printf("cmd_node->output_fd\t%i\n", cmd_node->output_fd);
		printf("cmd_node->output_path\t%s\n", cmd_node->output_path);
		printf("cmd_node->input_path\t%s\n", cmd_node->input_path);
		printf("cmd_node->is_heredoc\t%i\n", cmd_node->is_heredoc);
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
