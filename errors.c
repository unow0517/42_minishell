#include "minishell.h"

void	file_error(t_command *cmd_node)
{
	cmd_node->file_not_found = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_node->filename, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void	heredoc_error(t_command *cmd_node)
{
	cmd_node->file_not_found = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("/tmp/heredoc", 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void	cmd_error(t_command *cmd_node)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_node->cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(127);
}

void	unexpected_token(t_shell *shell_info, char *flag, int *status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (shell_info->tokens->token_type == WORD)
		ft_putstr_fd(get_first_word(shell_info->tokens->content), 2);
	else
		ft_putstr_fd(flag, 2);
	ft_putstr_fd("'\n", 2);
	shell_info->syntax_error = true;
	*status = 258;
}

void	quote_error(int *status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("syntax error: ", 2);
	ft_putstr_fd("can't handle unclosed quotes\n", 2);
	*status = 258;
}
