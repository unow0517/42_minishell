/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:36 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/25 11:55:11 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include "Libft/libft.h"
# include "ft_printf/ft_printf.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SHE 0
# define DFL 1
# define IGN 2

//added by thalia
typedef enum e_token_type
{
	NO_TOKEN,	//0
	WORD,		//1
	PIPE,		//2
	S_QUOTE,	//3
	D_QUOTE,	//4
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
	char			*content; //get_first_word(toke->content) cat hi hel > out
	t_token_type	token_type;
	struct s_token	*next;
	// char			*user_input_element;
} t_token;

typedef struct s_command
{
	// ls -lah LibFt
	char	*cmd;
	// char	*cmd_path;
	char	**options;
	char	**full_cmd;
	int		input_fd;
	int		output_fd;
	// char	*output_path; // path to output file
	// char	*input_path; // path to input file
	int		is_heredoc; // 0 if no << otherwise set to 1
	int		fd[2];
	int		file_not_found;
	char	*filename;
	bool	is_builtin;
	char	*builtin_type;
	char	*builtin_arg;
	char	*to_split;
	struct	s_command *next;
} t_command;

typedef struct s_env_mini
{
	char				*name;
	char				*value;
	struct s_env_mini	*next;
}	t_env_mini;

typedef struct s_shell
{
	int			argc;
	char		**argv;
	char		**env;
	t_env_mini	*env_mini;
	char		cwd[1024];
	char    	oldpwd[1024];
	t_token		*tokens;
	char		*user_input;
	char		prompt[1024];
	t_command	*first_command;
	int			fd[2];
	bool		syntax_error;
				//Its in linux/limits.h.
				// #define PATH_MAX        4096 
	int			*status;
	bool		isheredoc;
}	t_shell;

//inpt_functions.C
int		inputis(char *inpt, char *string);
int		inputstartswith(char *inpt, char *string);
int		inputhas(char *input, char c);

//HISTORY.C
void	print_history(t_shell *shell_info);

//SIG_FUNCTIONS.C
void	sighandler(int sig);
void	sigchecker(int sigint, int sigquit);
void	catchsignal(void);

//PWD.C
void	run_pwd(t_shell *shell_info);

//PIPE.C
void	execute(char *full_path, char *argv, char **env);
// void	run_pipe(char *inpt);
void	run_pipe(char *inpt, char **argv, char **env);
char	*find_cmd_in_env(char *cmd, char **env);

//ECHO.C
void	run_echo(char *inpt, t_shell *shell_info);

//CD.C
void	run_cd(char *inpt, t_shell *shell_info);

//ENV.C
void	run_env(t_shell *shell_info);

//WHITE_SPACE.C
char	*rm_starting_ws(char *string);
char	*multiple_ws_to_single(char	*str);
char	*ptr_ws(char *inpt);

//CHECKS.C
void	print_token(t_token *token);
void	print_linked_tokens(t_token *token);
void	print_split(char **str);
void	print_cmd_list(t_command *cmd_node);
void	print_split_no_newline(char **str);
void	print_token_types(t_shell *shell_info);
void	syntax_error_check(t_shell *shell_info);

// //PIPEX_FUNCTIONS.C
char	*get_first_word(char *argv);
void	handle_error(char *str);
void	free_split_thalia(char **str);

//MINISHELL.C
void	inpt_handler(char **argv, t_shell *shell_info);
void	initialise_basics(int argc, char **argv, char **env, t_shell *info);
int		create_prompt(t_shell *shell_info);

//SET_NODES.C
void	create_tokens(t_shell *shell_info);
t_token	*create_single_token(t_shell *shell_info, int i);
t_token	*create_double_token(t_shell *shell_info, int i);

//UTILS
void		token_add_back(t_token **first_token, t_token *new);
t_token		*token_last(t_token *token);
int			skip_whitespace(char *inpt, int i);
int			num_of_remaining_cmds(t_command *cur);
int			num_of_total_cmds(t_command *cur);
t_command	*get_last_cmd(t_command *cmd);
void		close_fds(t_shell *shell_info, t_command *cur);
bool		is_metacharacter(char c);
bool		is_ws(char c);
void		cmd_add_back(t_command **first_token, t_command *new);
int			handle_exit(int status);
bool		is_metacharacter_type(int i);
int			token_count(t_shell *shell_info);
bool		is_redir(int i);
bool		is_redir_pipe(int i);
bool		is_redir_pipe_char(char i);
bool		ft_is_builtin(char *str);
char		*get_argument(char *argv);
bool		quotes_even(char *input);
char		*remove_unecessary_q(t_shell *shell_info);
bool		is_double(t_shell *shell_info, int i);
void		finalise_node(t_shell *shell_info, t_command *cmd_node);

//PARSING.C
void	parse_input(t_shell *shell_info);
void	parse_tokens(t_shell *shell_info);
int		number_of_tokens(t_shell *shell_info);
void	set_executable_nodes(t_shell *shell_info, t_token *iterate);
int		open_file(t_command *cmd_node, t_token *iterate, int flag);
void	initialise_cmd_node(t_command *cmd_node);
void	init_cmds_in_struct(t_command *cmd_node, char *to_split);

//PARSING_CASES.C
bool	builtin_case(t_token *iterate);
bool	empty_cmd_case(t_token *iterate, t_command *cmd_node);
bool	full_cmd_case(t_token *iterate, t_command *cmd_node);

//PARSING_HELPER.C
t_token	*initialize_cmd(t_shell *shell_info, t_token *iterate, t_command *cmd_node);
t_token	*initialize_cmd_options(t_shell *shell_info, t_token *iterate, t_command *cmd_node);
void	quote_removal_in_exec_arg(t_command *cur_cmd);
char	*rm_quotes(char *to_fix, char c);
char	first_quote(char *str);
t_token	*skip_q_tokens(t_token *iterate);
t_token	*handle_awk(t_shell *shell_info, t_token *iterate, t_command *cmd_node);

//EXECUTION.C
void	executor(t_shell *shell_info, t_command *cur);
void	init_pipe(t_shell *shell_info, t_command *cur);
void	handle_redir(t_shell *shell_info, t_command *cur);
void	execution_cases(t_shell *shell_info);
pid_t	exec_pipeline(t_shell *shell_info);
pid_t	exec_single_cmd(t_shell *shell_info, t_command	*cmd_to_exec);
void	pipe_handling(t_shell *shell_info, t_command *cur);
void	close_pipes(t_shell *shell_info);
void	execute_builtin(t_shell *shell_info, t_command *cur);
// void execute_builtin_no_fork(t_shell *shell_info, char *builtin, char *arg);

//ERRORS
void	file_error(t_command *cmd_node);
void	heredoc_error(t_command *cmd_node);
void	cmd_error(t_command *cmd_node);
void	unexpected_token(t_shell *shell_info, char *flag);
void	quote_error(t_shell *shell_info);

//EXPORT.C
t_env_mini *ft_lstnew_envmini(char *name, char *value);
t_env_mini *ft_lstlast_envmini(t_env_mini *lst);
void	run_export(char *str, t_shell *shell_info);

//DOLLAR_EXPAND.C
void	ft_expand(t_shell *shell_info);
void	replace_caret(t_shell *shell_info);

//UNSET.C
void	run_unset(t_shell *shell_info);

//FREES
void	free_tokens(t_token **shell_info);
void	free_cmd_list(t_command **cmds);
void	free_shell(t_shell *shell_info);

//QUOTES
char	*quote_handler(t_shell *shell_info, t_token *iterate, char *quoted_str, t_token_type flag);
t_token	*skip_quoted_str(t_token *to_skip, t_token_type flag);

//SPLIT_MS.C
char	**split_ms(char const *s, char c);
void	update_quote_state_str(const char *str, int *inside_sq, int *inside_dq, int i);

//BUILTIN_ARGS
char	*arg_for_export(t_token *cur);
void	update_quote_state(t_token *cur, int *inside_sq, int *inside_dq, int i);
void	update_quote_state_token(t_token *cur, int *inside_sq, int *inside_dq);
t_token	*skip_tokens_of_builtin_arg(t_token *iterate);
t_token	*initialise_builtin_type_arg(t_command *cmd_node, t_token *iterate);

//BACKSLASH.C
char	*backslash_piece(char	*str);

//REDIR.C
t_token	*set_redirections(t_command *cmd_node, t_token *iterate);
void	handle_heredoc(t_command *cmd_node, char *delimiter);
void	file_opener(t_command *cmd_node, int flag, char *file);

#endif
