#include "minishell.h"

void	parse_input(t_shell *shell_info)
{
	create_tokens(shell_info);
	parse_tokens(shell_info);
	print_cmd_list(shell_info->first_command);
}

void	parse_tokens(t_shell *shell_info)
{
	// t_command	*cmd_node;
	t_token		*iterate;
	int			len;

	// cmd_node = NULL;
	iterate = shell_info->tokens;
	len = number_of_tokens(shell_info);
	// cmd_node = ft_calloc(1, sizeof(t_command));
	// if (!shell_info->first_command)
	// 	shell_info->first_command = cmd_node;
	// initialise_cmd_node(cmd_node);
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
	// cmd_node->standard_input = STDIN_FILENO;
	// cmd_node->standard_output = STDOUT_FILENO;
	cmd_node->next = NULL;
}

void	set_executable_nodes(t_shell *shell_info, t_token *iterate)
{
	t_command	*cmd_node;
	char		*to_split;
	char		*temp;
	char		*temp1;

	while (iterate != NULL)
	{
		if (iterate->token_type == PIPE)
			iterate = iterate->next;
		to_split = "";
		cmd_node = NULL;
		if (!shell_info->first_command)
			shell_info->first_command = cmd_node;
		cmd_node = ft_calloc(1, sizeof(t_command));
		initialise_cmd_node(cmd_node);
		cmd_node->cmd = ft_calloc(1, sizeof(char));
		while (iterate != NULL && iterate->token_type != PIPE)
		{
			iterate = set_redirections(cmd_node, iterate);
			// if (iterate != NULL && iterate->token_type == WORD && cmd_node->cmd[0] == '\0' && iterate->token_type != PIPE)
			// 	cmd_node->cmd = get_first_word(iterate->content);
			// else if (iterate && iterate->token_type == WORD && cmd_node->cmd == NULL && iterate->token_type != PIPE)
			// 	cmd_node->cmd = get_first_word(iterate->content);
			if (iterate && iterate->token_type == WORD && (cmd_node->cmd == NULL || cmd_node->cmd[0] == '\0') && iterate->token_type != PIPE)
				cmd_node->cmd = get_first_word(iterate->content);
			else if (iterate && iterate->token_type == WORD && cmd_node->cmd != NULL && cmd_node->cmd[0] != '\0' && iterate->token_type != PIPE)
			{
				temp = ft_strjoin(to_split, " ");
				temp1 = get_first_word(iterate->content); //-l
				to_split = ft_strjoin(temp, get_first_word(iterate->content));
				to_split = ft_strjoin(temp, temp1);
				free(temp);
				free(temp1);
			}
			if (iterate)
				iterate = iterate->next;
		}
		init_cmds_in_struct(cmd_node, to_split);
		cmd_add_back(&shell_info->first_command, cmd_node);
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
	cmd_node->full_cmd = ft_split(to_full_cmd, ' ');
	if (!temp_cmd)
	{
		perror("ft_strjoin(cmd_node->cmd, " ") FAILED");
		exit (-1);
	}
	cmd_node->options = ft_split(to_split, ' ');
	if (!temp_cmd)
	{
		perror("ft_strjoin(cmd_node->cmd, " ") FAILED");
		exit (-1);
	}
}

t_token	*set_redirections(t_command *cmd_node, t_token *iterate)
{
	t_token	*init_tok;

	init_tok = iterate;
	if (iterate->token_type == S_LESS)
	{
		iterate = iterate->next;
		if (open_file(cmd_node, iterate, S_LESS) == -1)
		{
			printf("failed to open file\n");
			return (init_tok);// fix return/exit and frees
		}
		iterate = iterate->next;
	}
	else if (iterate->token_type == D_LESS)
	{
		cmd_node->is_heredoc = 1;
		// if (open_file(cmd_node, iterate, D_LESS) == -1)
		// 	return (NULL);
	}
	else if (iterate && iterate->token_type == S_MORE && iterate->next && iterate->next->token_type == WORD) //create open file function to pass enum
	{
		iterate = iterate->next;
		if (open_file(cmd_node, iterate, S_MORE) == -1)
		{
			printf("failed to open file\n");
			return (init_tok);// fix return/exit and frees
		}
		iterate = iterate->next;
	}
	else if (iterate && iterate->token_type == D_MORE && iterate->next && iterate->next->token_type == WORD) //create open file function to pass enum
	{
		// printf("entered if statement\n");
		iterate = iterate->next;
		if (open_file(cmd_node, iterate, D_MORE) == -1)
		{
			printf("failed to open file\n");
			return (init_tok);// fix return/exit and frees
		}
		iterate = iterate->next;
	}
	return (iterate);
}

int	open_file(t_command *cmd_node, t_token *iterate, int flag)
{
	char	*file;

	file = get_first_word(iterate->content);
	if (flag == S_LESS)
		cmd_node->input_fd = open(file, O_RDONLY);
	else if (flag == S_MORE)
		cmd_node->output_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (flag == D_MORE)
		cmd_node->output_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (flag == D_LESS)
	{
		//handle heredoc
	}
	free(file);
	if ((flag == S_MORE || flag == D_MORE) && cmd_node->output_fd == -1) // add checks
		return (-1);
	else if (flag == S_LESS && cmd_node->input_fd ==  -1)
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
