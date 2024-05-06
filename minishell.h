/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:36 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/06 18:29:06 by tsimitop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "Libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <sys/wait.h>
# include <fcntl.h>

# define SHE 0
# define DFL 1
# define IGN 2

//added by thalia
typedef enum e_token_type
{
	NO_TOKEN,
	WORD,
	PIPE,
	S_QUOTE,
	D_QUOTE,
	S_LESS, // < input redirection
	S_MORE, // > output redirection
	D_LESS, // <<
	D_MORE  // >>
}	t_token_type;

typedef struct s_token //token, not token
{
	char			*input;
	int				len;
	int				idx;
	char			*content;
	t_token_type	token_type;
	struct s_token	*next;
	// char			*user_input_element;
} t_token;

typedef struct s_command
{
	// ls -lah LibFt
	char	*cmd; // "ls"
	char	**options; // ["-lah", "LibFt"]
	char	**full_cmd; // ["ls", "-lah", "LibFt"]
	int		input_fd; // -1 (if no input < OR <<) otherwise set fd to opened file fd
	int		output_fd; // -f (if no output > OR >>) otherwise set fd to opened file fd
	char	*output_path; // path to output file
	char	*input_path; // path to input file
	int		is_heredoc; // 0 if no << otherwise set to 1
	struct	s_command *next;
} t_command;

typedef struct s_shell
{
	int			argc;
	char		**argv;
	char		**env;
	char		cwd[1024];
	t_token		*tokens;
	char		*user_input;
	char		prompt[1024];
	t_command	*first_command;
				//Its in linux/limits.h.
				// #define PATH_MAX        4096 
}	t_shell;

//inpt_functions.C
int		inputis(char *inpt, char *string);
int		inputstartswith(char *inpt, char *string);
int		inputhas(char *input, char c);

//HISTORY.C
void	print_history(char *inpt);

//SIG_FUNCTIONS.C
void	sighandler(int sig);
void	sigchecker(int sigint, int sigquit);
void	catchsignal(void);

//PWD.C
void	printpwd(t_shell *shell_info);

//PIPE.C
void	execute(char *full_path, char *argv, char **env);
// void	run_pipe(char *inpt);
void	run_pipe(char *inpt, char **argv, char **env);
char	*find_cmd_in_env(char *cmd, char **env);

//ECHO.C
void	run_echo(char *inpt);

//CD.C
void	run_cd(char *inpt, t_shell *shell_info);

//ENV.C
void	run_env(char *inpt, char **env);

//WHITE_SPACE.C
char	*rm_starting_ws(char *string);
char	*multiple_ws_to_single(char	*str);

//CHECKS.C
void	print_token(t_token *token);
void	print_linked_tokens(t_token *token);
void	print_split(char **str);
void	print_cmd_list(t_command *cmd_node);
void	print_split_no_newline(char **str);

// //PIPEX_FUNCTIONS.C
char	*get_first_word(char *argv);
void	handle_error(char *str);
void	free_split_thalia(char **str);

//MINISHELL.C
void	inpt_handler(char **argv, char **env, t_shell *info);
void	initialise_basics(int argc, char **argv, char **env, t_shell *info);
int		create_prompt(t_shell *shell_info);


//SET_NODES.C
int	create_tokens(t_shell *shell_info);
t_token	*create_single_token(t_shell *shell_info, int i);
t_token	*create_double_token(t_shell *shell_info, int i);

//UTILS
void	token_add_back(t_token **first_token, t_token *new);
t_token	*token_last(t_token *token);
int		skip_whitespace(char *inpt, int i);

//PARSING.C
void	parse_input(t_shell *shell_info);
void	parse_tokens(t_shell *shell_info);
int		number_of_tokens(t_shell *shell_info);
void	set_executable_nodes(t_command *cmd_node, t_token *iterate);
t_token	*set_redirections(t_command *cmd_node, t_token *iterate);
int		open_file(t_command *cmd_node, t_token *iterate, int flag);
void	initialise_cmd_node(t_command *cmd_node);

//EXECUTING
void	executor(t_shell *shell_info, int *status, t_command *cur);
void	handle_redir(t_command *cur);

//FREES
void	free_tokens(t_token **shell_info);
void	free_cmd_list(t_command **cmds);

#endif
