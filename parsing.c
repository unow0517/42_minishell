#include "minishell.h"

void	parse_input(t_shell *shell_info)
{
	create_tokens(shell_info);
	parse_tokens(shell_info);
}

void	parse_tokens(t_shell *shell_info)
{
	t_command	*cmd_node;
	t_token	*iterate;
	int			len;

	iterate = shell_info->tokens;
	len = number_of_tokens(shell_info);
	// if (len > 1)
	// 	create_pipe(shell_info, len?);
	while (iterate != NULL && iterate->token_type != PIPE)
	{
		if (iterate->token_type == WORD && iterate->next->token_type == WORD) //wrong logic
		{
			//iterate to count how many are words and then first = cmd rest = options
			//make sure to check for < << > >> ' "
		}
	}
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
