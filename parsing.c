#include "minishell.h"

void	parse_input(t_shell *shell_info)
{
	create_tokens(shell_info);
	parse_tokens(shell_info);
	// print_cmd_list(shell_info->first_command);
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
	cmd_node->next = NULL;
}

//PROCESS THE CMD ACCORDING TO TOKENS
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
// printf("HEYYYYYYYYY\n");
			iterate = set_redirections(cmd_node, iterate);
			if (iterate && (iterate->token_type == WORD || iterate->token_type == D_QUOTE || iterate->token_type == S_QUOTE) && (cmd_node->cmd == NULL || cmd_node->cmd[0] == '\0') && iterate->token_type != PIPE)
			{
				if (iterate->token_type == WORD)
					cmd_node->cmd = get_first_word(iterate->content);
				else if (iterate->token_type == D_QUOTE)
				{
					iterate = iterate->next;
					cmd_node->cmd = quote_handler(shell_info, iterate, quoted_str, D_QUOTE);
					iterate = skip_quoted_str(iterate, D_QUOTE);
				}
				else if (iterate->token_type == S_QUOTE)
				{
					iterate = iterate->next;
					cmd_node->cmd = quote_handler(shell_info, iterate, quoted_str, S_QUOTE);
					iterate = skip_quoted_str(iterate, S_QUOTE);
				}
// printf("cmd_node->cmd = %s\n", cmd_node->cmd);
			}
			else if (iterate && (iterate->token_type == WORD || iterate->token_type == D_QUOTE || iterate->token_type == S_QUOTE) && cmd_node->cmd != NULL && cmd_node->cmd[0] != '\0' && iterate->token_type != PIPE)
			{
				if (iterate->token_type == D_QUOTE) //make sure they are duplicates
				{
					iterate = iterate->next;
					quoted_str = quote_handler(shell_info, iterate, quoted_str, D_QUOTE);
					temp = ft_strjoin(to_split, " ");
					temp1 = quoted_str; //-l
					to_split = ft_strjoin(temp, quoted_str);
					to_split = ft_strjoin(temp, temp1);
					free(temp);
					// free(temp1);
					iterate = skip_quoted_str(iterate, D_QUOTE);
				}
				else if (iterate->token_type == S_QUOTE) //make sure they are duplicates
				{
					iterate = iterate->next;
					quoted_str = quote_handler(shell_info, iterate, quoted_str, S_QUOTE);
					temp = ft_strjoin(to_split, " ");
					temp1 = quoted_str; //-l
					to_split = ft_strjoin(temp, quoted_str);
					to_split = ft_strjoin(temp, temp1);
					free(temp);
					// free(temp1);
					iterate = skip_quoted_str(iterate, S_QUOTE);
				}
				else
				{
					temp = ft_strjoin(to_split, " ");
					temp1 = get_first_word(iterate->content); //-l
					to_split = ft_strjoin(temp, get_first_word(iterate->content));
					to_split = ft_strjoin(temp, temp1);
					free(temp);
					free(temp1);
				}
			}
			if (iterate && is_metacharacter_type(iterate->token_type) == false)
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

//>, <
t_token	*set_redirections(t_command *cmd_node, t_token *iterate)
{
	t_token	*init_tok;

	init_tok = iterate;
	if (iterate->token_type == S_LESS) //<
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

//OPEN FILE TAKING TOKEN STRUCT
int	open_file(t_command *cmd_node, t_token *iterate, int flag)
{
	char	*file;

	file = get_first_word(iterate->content);
	if (flag == S_LESS) //<
	{
		// IF NODE INPUT FD HAS ANOTHER FD, CLOSE
		if (cmd_node->input_fd != -1)
			close(cmd_node->input_fd);
		cmd_node->input_fd = open(file, O_RDONLY); //
	}
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
