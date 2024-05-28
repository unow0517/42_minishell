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

void	env_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	exit(127);
}
