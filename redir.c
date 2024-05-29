/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:34:02 by tsimitop          #+#    #+#             */
/*   Updated: 2024/05/29 12:34:10 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*simple_file_redir(t_command *cmd_node, t_token *iter, \
t_token_type flag)
{
	t_token_type	hold;

	iter = iter->next;
	hold = iter->token_type;
	if (iter && (iter->token_type == S_QUOTE || iter->token_type == D_QUOTE))
		iter = skip_q_tokens(iter);
	if (cmd_node->file_not_found == 0)
		cmd_node->filename = get_first_word(iter->content);
	if (cmd_node->file_not_found == 0)
	{
		if (open_file(cmd_node, iter, flag) == -1 || \
		access(cmd_node->filename, F_OK) == -1)
		{
			cmd_node->file_not_found = 1;
			file_error(cmd_node);
		}
	}
	if (iter && (hold == S_QUOTE || hold == D_QUOTE))
		iter = skip_q_tokens(iter);
	if (iter)
		iter = iter->next;
	return (iter);
}

static t_token	*heredoc_redir(t_command *cmd_node, t_token *iter)
{
	iter = iter->next;
	if (iter && (iter->token_type == S_QUOTE || iter->token_type == D_QUOTE))
		iter = skip_q_tokens(iter);
	cmd_node->is_heredoc = 1;
	if (open_file(cmd_node, iter, D_LESS) == -1 || \
	access("/tmp/heredoc", F_OK) == -1)
	{
		cmd_node->file_not_found = 1;
		heredoc_error(cmd_node);
	}
	if (iter && (iter->token_type == S_QUOTE || iter->token_type == D_QUOTE))
		iter = skip_q_tokens(iter);
	else if (iter)
		iter = iter->next;
	return (iter);
}

t_token	*set_redirections(t_command *cmd_node, t_token *iterate)
{
	if (iterate && iterate->token_type == S_LESS)
		iterate = simple_file_redir(cmd_node, iterate, S_LESS);
	else if (iterate && iterate->token_type == D_LESS)
		iterate = heredoc_redir(cmd_node, iterate);
	else if (iterate && iterate->token_type == S_MORE)
		iterate = simple_file_redir(cmd_node, iterate, S_MORE);
	else if (iterate && iterate->token_type == D_MORE)
		iterate = simple_file_redir(cmd_node, iterate, D_MORE);
	return (iterate);
}

void	handle_heredoc(t_command *cmd_node, char *delimiter)
{
	char	*here_line;
	int		fd;

	here_line = NULL;
	fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	here_line = readline(">");
	while (here_line)
	{
		if (here_line[0] != '\0' && ft_strncmp(delimiter, here_line, \
		ft_strlen(delimiter)) == 0 && ft_strncmp(delimiter, here_line, \
		ft_strlen(here_line)) == 0)
			break ;
		ft_putstr_fd(here_line, fd);
		ft_putstr_fd("\n", fd);
		free(here_line);
		here_line = readline(">");
	}
	if (here_line)
		free(here_line);
	close(fd);
	cmd_node->input_fd = open("/tmp/heredoc", O_RDONLY);
	if (cmd_node->input_fd == -1)
		printf("failed to open /tmp/heredoc\n");
}

void	file_opener(t_command *cmd_node, int flag, char *file)
{
	if (flag == S_LESS)
	{
		if (cmd_node->input_fd != -1)
			close(cmd_node->input_fd);
		cmd_node->input_fd = open(file, O_RDONLY);
	}
	else if (flag == S_MORE)
	{
		if (cmd_node->output_fd != -1)
			close(cmd_node->output_fd);
		cmd_node->output_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (flag == D_MORE)
	{
		if (cmd_node->output_fd != -1)
			close(cmd_node->output_fd);
		cmd_node->output_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if (flag == D_LESS)
	{
		if (cmd_node->input_fd != -1)
			close(cmd_node->input_fd);
		handle_heredoc(cmd_node, file);
	}
}
