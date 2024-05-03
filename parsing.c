#include "minishell.h"

void	parse_input(t_shell *shell_info)
{
	create_tokens(shell_info);
	parse_tokens(shell_info);
}

void	parse_tokens(t_shell *shell_info)
{
	t_command	*cmd_node;
	t_token		*iterate;
	int			len;

	cmd_node = NULL;
	if (!shell_info->first_command)
		shell_info->first_command = cmd_node;
	iterate = shell_info->tokens;
	len = number_of_tokens(shell_info);
	cmd_node = ft_calloc(1, sizeof(t_command));
	initialise_cmd_node(cmd_node);
	// if (len > 1)
	// 	create_pipe(shell_info, len?);
	set_executable_nodes(cmd_node, iterate);
}

void	initialise_cmd_node(t_command *cmd_node)
{
	cmd_node->cmd = ft_calloc(1, sizeof(char));
	cmd_node->options = NULL;
	cmd_node->full_cmd = NULL;
	cmd_node->input_fd = -1;
	cmd_node->output_fd = -1;
	cmd_node->input_path = NULL;
	cmd_node->output_path = NULL;
	cmd_node->is_heredoc = 0;
	cmd_node->next = NULL;
}

void	set_executable_nodes(t_command *cmd_node, t_token *iterate)
{
	char	*to_split;
	char	*to_full_cmd;
	char	*temp;
	char	*temp_cmd;

	// to_split = ft_calloc(1, sizeof(char));
	// cmd_node->cmd = ft_calloc(1, sizeof(char));
	while (iterate != NULL && iterate->token_type != PIPE)
	{
		iterate = set_redirections(cmd_node, iterate);
		if (iterate != NULL && iterate->token_type == WORD && cmd_node->cmd == NULL && iterate->token_type != PIPE)
			cmd_node->cmd = ft_substr(iterate->input, iterate->idx, iterate->len);
		else if (iterate && iterate->token_type == WORD && cmd_node->cmd == NULL && iterate->token_type != PIPE)
			cmd_node->cmd = ft_substr(iterate->content, iterate->idx, iterate->len);
		else if (iterate && iterate->token_type == WORD && cmd_node->cmd != NULL && iterate->token_type != PIPE)
		{
			temp = ft_strjoin(to_split, " ");
			to_split = ft_strjoin(temp, ft_substr(iterate->content, iterate->idx, iterate->len));
			free(temp);
		}
		if (iterate)
			iterate = iterate->next;
	}
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
	if (iterate->token_type == S_LESS) //create open file function to pass enum
	{
		if (open_file(cmd_node, iterate, S_LESS) == -1)
			return (NULL);// fix return/exit and frees
		iterate = iterate->next;
	}
	else if (iterate->token_type == D_LESS) //create open file function to pass enum
	{
		// if (open_file(cmd_node, iterate, D_LESS) == -1)
		// 	return (NULL);
		//heredoc case;
	}
	else if (iterate->token_type == WORD && iterate->next && iterate->next->token_type == S_MORE) //create open file function to pass enum
	{
		if (open_file(cmd_node, iterate, S_MORE) == -1)
			return (NULL);// fix return/exit and frees
		iterate = iterate->next;
	}
	else if (iterate->token_type == WORD && iterate->next && iterate->next->token_type == D_MORE) //create open file function to pass enum
	{
		if (open_file(cmd_node, iterate, D_MORE) == -1)
			return (NULL);// fix return/exit and frees
		iterate = iterate->next;
	}
	if (iterate)
		iterate = iterate->next;
	return (iterate);
}

int	open_file(t_command *cmd_node, t_token *iterate, int flag)
{
	if (flag == S_LESS)
		cmd_node->input_fd = open(ft_substr(iterate->input, iterate->idx, iterate->len), O_RDONLY);
	else if (flag == S_MORE)
		cmd_node->output_fd = open(ft_substr(iterate->input, iterate->idx, iterate->len), O_WRONLY | O_CREAT | O_TRUNC);
	else if (flag == D_MORE)
		cmd_node->output_fd = open(ft_substr(iterate->input, iterate->idx, iterate->len), O_WRONLY | O_CREAT | O_APPEND);
	else if (flag == D_LESS)
	{
		//handle heredoc
	}
	if (cmd_node->output_fd == -1) // add checks
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
