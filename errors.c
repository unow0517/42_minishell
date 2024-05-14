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
