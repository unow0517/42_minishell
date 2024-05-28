#include "minishell.h"

void	parse_input(t_shell *shell_info)
{
	if (quotes_even(shell_info->user_input) == true)
	{
		create_tokens(shell_info);
		syntax_error_check(shell_info);
		if (shell_info->syntax_error == false)
			parse_tokens(shell_info);
		// print_token(shell_info->tokens); //delete
		// print_cmd_list(shell_info->first_command); //delete
	}
	else
		quote_error(shell_info);
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

//PROCESS THE CMD ACCORDING TO TOKENS
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
		while (iterate != NULL && iterate->token_type != PIPE)
		{
			if (is_redir(iterate->token_type) == true)
				iterate = set_redirections(cmd_node, iterate);
			else if (iterate && builtin_case(iterate) == true)
				iterate = initialise_builtin_type_arg(cmd_node, iterate);
			else if (iterate && empty_cmd_case(iterate, cmd_node) == true)
				iterate = initialize_cmd(iterate, cmd_node);
			else if (iterate && full_cmd_case(iterate, cmd_node) == true)
				iterate = initialize_cmd_options(iterate, cmd_node);
		}
		finalise_node(shell_info, cmd_node);
	}
}

void	init_cmds_in_struct(t_command *cmd_node, char *to_split)
{
	char	*to_full_cmd;
	char	*temp_cmd;

	to_full_cmd = NULL;
	temp_cmd = NULL;
	if (cmd_node->cmd)
		temp_cmd = ft_strjoin(cmd_node->cmd, " ");
	if (cmd_node->cmd && to_split)
		to_full_cmd = ft_strjoin(temp_cmd, to_split);
	if (cmd_node->cmd && to_full_cmd)
		cmd_node->full_cmd = split_ms(to_full_cmd, ' ');
	if (to_split)
		cmd_node->options = split_ms(to_split, ' ');
	if (temp_cmd)
		free(temp_cmd);
	if (to_full_cmd)
		free(to_full_cmd);
}

//OPEN FILE TAKING TOKEN STRUCT
int	open_file(t_command *cmd_node, t_token *iterate, int flag)
{
	char	*file;

	file = get_first_word(iterate->content);
	if (file)
	{
		file_opener(cmd_node, flag, file);
		free(file);
	}
	if ((flag == S_MORE || flag == D_MORE) && cmd_node->output_fd == -1)
		return (-1);
	else if (flag == S_LESS && cmd_node->input_fd == -1)
		return (-1);
	else
		return (0);
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
