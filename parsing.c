#include "minishell.h"

void	parse_input(t_shell *shell_info, int *status)
{

	if (quotes_even(shell_info->user_input) == true)
	{
		create_tokens(shell_info);
		syntax_error_check(shell_info, status);
		if (shell_info->syntax_error == false)
			parse_tokens(shell_info);
		// print_token_types(shell_info);
		print_cmd_list(shell_info->first_command);
	}
	else
		quote_error(status);
}

void	parse_tokens(t_shell *shell_info)
{
	t_token		*iterate;

	iterate = shell_info->tokens;
	set_executable_nodes(shell_info, iterate);
}

void	initialise_cmd_node(t_command *cmd_node)
{
	cmd_node->cmd = NULL;
	cmd_node->options = NULL;
	cmd_node->full_cmd = NULL;
	cmd_node->input_fd = -1;
	cmd_node->output_fd = -1;
	cmd_node->input_path = NULL;
	cmd_node->output_path = NULL;
	cmd_node->is_heredoc = 0;
	pipe(cmd_node->fd);
	cmd_node->file_not_found = 0;
	cmd_node->filename = NULL;
	cmd_node->is_builtin = false;
	cmd_node->to_split = "";
	cmd_node->is_builtin = 0;
	cmd_node->builtin_type = NULL;
	cmd_node->builtin_arg = NULL;
	cmd_node->next = NULL;
}

void	set_executable_nodes(t_shell *shell_info, t_token *iterate)
{
	t_command	*cmd_node;

	while (iterate != NULL)
	{
		if (iterate->token_type == PIPE)
			iterate = iterate->next;
		cmd_node = NULL;
		if (!shell_info->first_command)
			shell_info->first_command = cmd_node;
		cmd_node = ft_calloc(1, sizeof(t_command));
		initialise_cmd_node(cmd_node);
		cmd_node->cmd = ft_calloc(1, sizeof(char));
		while (iterate != NULL && iterate->token_type != PIPE)
		{
			if (is_redir(iterate->token_type) == true)
				iterate = set_redirections(cmd_node, iterate);
			else if (iterate && builtin_case(iterate) == true)
			{
				cmd_node->builtin_type = get_first_word(iterate->content);
				cmd_node->is_builtin = true;
				iterate = iterate->next;
				if (iterate)
					cmd_node->builtin_arg = arg_for_export(iterate);
				iterate = skip_tokens_of_builtin_arg(iterate);
			}
			else if (iterate && empty_cmd_case(iterate, cmd_node) == true)
				iterate = initialize_cmd(shell_info, iterate, cmd_node);
			else if (iterate && full_cmd_case(iterate, cmd_node) == true)
				iterate = initialize_cmd_options(shell_info, iterate, cmd_node);
		}
		init_cmds_in_struct(cmd_node, cmd_node->to_split);
		cmd_add_back(&shell_info->first_command, cmd_node);
		// if (cmd_node->cmd && ft_strncmp(cmd_node->cmd, "awk", 3) != 0)
		quote_removal_in_exec_arg(cmd_node);
	}
}

void	init_cmds_in_struct(t_command *cmd_node, char *to_split)
{
	char	*to_full_cmd;
	char	*temp_cmd;

	temp_cmd = ft_strjoin(cmd_node->cmd, " ");
	if (!temp_cmd)
	{
		perror("ft_strjoin(cmd_node->cmd, " ") FAILED");
		exit (-1);
	}
	to_full_cmd = ft_strjoin(temp_cmd, to_split);
	if (!temp_cmd)
	{
		perror("ft_strjoin(cmd_node->cmd, " ") FAILED");
		exit (-1);
	}
	cmd_node->full_cmd = split_ms(to_full_cmd, ' ');
	if (!temp_cmd)
	{
		perror("ft_strjoin(cmd_node->cmd, " ") FAILED");
		exit (-1);
	}
	cmd_node->options = split_ms(to_split, ' ');
	if (!temp_cmd)
	{
		perror("ft_strjoin(cmd_node->cmd, " ") FAILED");
		exit (-1);
	}
}

t_token	*set_redirections(t_command *cmd_node, t_token *iterate)
{
	if (iterate && iterate->token_type == S_LESS)
	{
		iterate = iterate->next;
		if (iterate && (iterate->token_type == S_QUOTE || iterate->token_type == D_QUOTE))
			iterate = skip_q_tokens(iterate);
		if (cmd_node->file_not_found == 0)
			cmd_node->filename = get_first_word(iterate->content);
		if (cmd_node->file_not_found == 0)
		{
			if (open_file(cmd_node, iterate, S_LESS) == -1 || access(get_first_word(iterate->content), F_OK) == -1)
			{
				cmd_node->file_not_found = 1;
				file_error(cmd_node);
			}
		}
		if (iterate && (iterate->token_type == S_QUOTE || iterate->token_type == D_QUOTE))
			iterate = skip_q_tokens(iterate);
		if (iterate)
			iterate = iterate->next;
	}
	else if (iterate && iterate->token_type == D_LESS)
	{
		iterate = iterate->next;
		if (iterate && (iterate->token_type == S_QUOTE || iterate->token_type == D_QUOTE))
			iterate = skip_q_tokens(iterate);
		cmd_node->is_heredoc = 1;
		if (open_file(cmd_node, iterate, D_LESS) == -1 || access("/tmp/heredoc", F_OK) == -1)
		{
			cmd_node->file_not_found = 1;
			heredoc_error(cmd_node);
		}
		if (iterate && (iterate->token_type == S_QUOTE || iterate->token_type == D_QUOTE))
			iterate = skip_q_tokens(iterate);
		if (iterate)
			iterate = iterate->next;
	}
	else if (iterate && iterate->token_type == S_MORE) //create open file function to pass enum// && iterate->next && iterate->next->token_type == WORD
	{
		iterate = iterate->next;
		if (iterate && (iterate->token_type == S_QUOTE || iterate->token_type == D_QUOTE))
			iterate = skip_q_tokens(iterate);
		if (cmd_node->file_not_found == 0)
			cmd_node->filename = get_first_word(iterate->content);
		if (cmd_node->file_not_found == 0)
		{
			if (open_file(cmd_node, iterate, S_MORE) == -1 || access(get_first_word(iterate->content), F_OK) == -1)
				file_error(cmd_node);
		}
		if (iterate && (iterate->token_type == S_QUOTE || iterate->token_type == D_QUOTE))
			iterate = skip_q_tokens(iterate);
		if (iterate)
			iterate = iterate->next;
	}
	else if (iterate && iterate->token_type == D_MORE) // && iterate->next && iterate->next->token_type == WORD
	{
		iterate = iterate->next;
		if (iterate && (iterate->token_type == S_QUOTE || iterate->token_type == D_QUOTE))
			iterate = skip_q_tokens(iterate);
		if (cmd_node->file_not_found == 0)
			cmd_node->filename = get_first_word(iterate->content);
		if (cmd_node->file_not_found == 0)
		{
			if (open_file(cmd_node, iterate, D_MORE) == -1 || access(get_first_word(iterate->content), F_OK) == -1)
				file_error(cmd_node);
		}
		if (iterate && (iterate->token_type == S_QUOTE || iterate->token_type == D_QUOTE))
			iterate = skip_q_tokens(iterate);
		if (iterate)
			iterate = iterate->next;
	}
	return (iterate);
}

int	open_file(t_command *cmd_node, t_token *iterate, int flag)
{
	char	*file;

	file = get_first_word(iterate->content);
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
	free(file);
	if ((flag == S_MORE || flag == D_MORE) && cmd_node->output_fd == -1) // add checks
		return (-1);
	else if (flag == S_LESS && cmd_node->input_fd ==  -1)
		return (-1);
	else
		return (0);
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
		printf("failed to open /tmp/heredoc\n"); //fix error or return value
}

int	number_of_tokens(t_shell *shell_info)
{
	t_token	*iterate;
	int		counter;

	counter = 0;
	iterate = shell_info->tokens;
	while (iterate != NULL)
	{
		iterate = iterate->next;
		counter++;
	}
	return (counter);
}
