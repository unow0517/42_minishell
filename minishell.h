/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:36 by yowoo             #+#    #+#             */
/*   Updated: 2024/05/31 14:35:04 by tsimitop         ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SHE 0
# define DFL 1
# define IGN 2

typedef enum e_token_type
{
	NO_TOKEN,
	WORD,
	PIPE,
	S_QUOTE,
	D_QUOTE,
	S_LESS,
	S_MORE,
	D_LESS,
	D_MORE
}	t_token_type;

typedef struct s_token
{
	char				*input;
	int					len;
	int					idx;
	char				*content;
	t_token_type		token_type;
	struct s_token		*next;
}	t_token;

typedef struct s_command
{
	char				*cmd;
	char				**options;
	char				**full_cmd;
	int					input_fd;
	int					output_fd;
	int					is_heredoc;
	int					fd[2];
	int					file_not_found;
	char				*filename;
	bool				is_builtin;
	char				*builtin_type;
	char				*builtin_arg;
	char				*to_split;
	struct s_command	*next;
}	t_command;

typedef struct s_env_mini
{
	char				*name;
	char				*value;
	struct s_env_mini	*next;
}	t_env_mini;

typedef struct s_shell
{
	int					argc;
	char				**argv;
	char				**env;
	t_env_mini			*env_mini;
	char				cwd[2048];
	char				oldpwd[2048];
	t_token				*tokens;
	char				*user_input;
	char				prompt[2048];
	t_command			*first_command;
	int					fd[2];
	bool				syntax_error;
	int					*status;
	bool				isheredoc;
	char				*temp;
}	t_shell;

typedef struct s_awk_data
{
	char	*to_split_options;
	char	*to_split_options_rest;
	char	*temp;
}	t_awk_data;

// AWK.C
t_token		*handle_awk(t_token *iterate, t_command *cmd_node);

// AWK_UTILS.C
int			awk_sqlen(t_token *iterate);
int			awk_restlen(t_token *iterate, int *sq, int *dq);
t_token		*skip_awk(t_token *iterate, int *sq, int *dq);

//BUILTIN_ARGS.C
char		*arg_for_export(t_token *cur);
t_token		*skip_tokens_of_builtin_arg(t_token *iterate);
t_token		*initialise_builtin_type_arg(t_command *cmd_node, t_token *iterate);

//CD.C
void		run_cd(char *inpt, t_shell *shell_info);
void		update_pwd(char *str, t_shell *shell_info);

//CHECKS.C
void		print_token(t_token *token);
void		print_split(char **str);
void		print_cmd_list(t_command *cmd_node);
void		print_split_no_newline(char **str);
void		print_token_types(t_shell *shell_info);

//ECHO.C
void		run_echo(char *inpt, t_shell *shell_info, int fd);

//ENV.C
void		run_env(t_shell *shell_info);

//ERRORS.C
void		file_error(t_command *cmd_node);
void		heredoc_error(t_command *cmd_node);
void		cmd_error(t_command *cmd_node);
void		unexpected_token(t_shell *shell_info, char *flag);
void		quote_error(t_shell *shell_info);
void		env_error(char *cmd);

//EXECUTION.C
void		handle_redir(t_shell *shell_info, t_command *cur);
void		execution_cases(t_shell *shell_info);
pid_t		exec_pipeline(t_shell *shell_info);
pid_t		exec_single_cmd(t_shell *shell_info, t_command	*cmd_to_exec);
void		pipe_handling(t_shell *shell_info, t_command *cur);
void		close_pipes(t_shell *shell_info);
void		execute_builtin(t_shell *shell_info, t_command *cur);
void		fork_fail(void);
void		execute_cmd(t_shell *shell_info, t_command *cmd_to_exec, \
char *full_path, char **paths_in_env);
void		free_exec_paths(char *full_path, char **paths_in_env);

//EXPAND_REPLACES.C
void		replace_bs_dollar(t_shell *shell_info);
char		*replace_exp(char *inpt, char *var_value, int var_name_len);
void		replace_dollar_question(t_shell *shell_info);
void		replace_caret(t_shell *shell_info);
void		replace_exps_loop(t_shell *shell_info);

//EXPAND_UTIL_2.C
void		cpy_str(char *str, char *dst, int cnt);
void		update_quoted(char *str, int *i_sq);
void		exp_shell(char *str, int *i_sq, char *start, t_shell *shell_info);

//EXPAND_UTIL.C
int			is_al_num_udsc_c(char c);
int			ft_varname_len(char *str);
char		*ft_varvalue(int var_name_len, char *str, t_env_mini *env_mini);
char		*join_three(char *str1, char *str2, char *str3);
void		rm_ws_aft_dl(char *before, char *after, t_shell *shell_info);

//EXPAND.C
void		ft_expand(t_shell *shell_info);

//EXPORT_UTILS.C
void		run_declare_env(t_shell *shell_info);
t_env_mini	*ft_lstnew_envmini(char *name, char *value);
t_env_mini	*ft_lstlast_envmini(t_env_mini *lst);
int			is_al_num_underscore(char *str);

//EXPORT.C
char		*export_rm_quote(char *str);
void		run_export_keyword(char	*str, t_shell *shell_info, int *status);
void		run_export(char *str, t_shell *shell_info);

//FREEING.C
void		free_tokens(t_token **shell_info);
void		free_cmd_list(t_command **cmds);
void		free_shell(t_shell *shell_info);
void		free_split_thalia(char **str);
void		free_temp(t_command *temp);

//HISTORY.C
void		print_history(t_shell *shell_info);

//INPT_FUNCTION.C
int			inputis(char *inpt, char *string);
int			inputstartswith(char *inpt, char *string);
int			inputhas(char *input, char c);

//MINISHELL.C
void		inpt_handler(t_shell *shell_info);
void		initialise_basics(char **argv, char **env, t_shell *info);
int			create_prompt(t_shell *shell_info);

//PARSING_CASES.C
bool		builtin_case(t_token *iterate);
bool		empty_cmd_case(t_token *iterate, t_command *cmd_node);
bool		full_cmd_case(t_token *iterate, t_command *cmd_node);

//PARSING_HELPER.C
t_token		*initialize_cmd(t_token *iterate, t_command *cmd_node);
t_token		*initialize_cmd_options(t_token *iterate, t_command *cmd_node);
void		quote_removal_in_exec_arg(t_command *cur_cmd);
char		*rm_quotes(char *to_fix, char c);
char		first_quote(char *str);
t_token		*skip_q_tokens(t_token *iterate);
t_token		*handle_awk(t_token *iterate, t_command *cmd_node);

//PARSING.C
void		parse_input(t_shell *shell_info);
void		parse_tokens(t_shell *shell_info);
int			number_of_tokens(t_shell *shell_info);
void		set_executable_nodes(t_shell *shell_info, t_token *iterate);
int			open_file(t_command *cmd_node, t_token *iterate, int flag);
void		initialise_cmd_node(t_command *cmd_node);
void		init_cmds_in_struct(t_command *cmd_node, char *to_split);
void		update_quote_state(t_token *cur, int *sq, int *dq, int i);
void		update_quote_state_token(t_token *cur, int *sq, int *dq);

//PIPE.C
char		*find_cmd_in_env_mini(char *cmd, char **env);

//PWD.C
void		run_pwd(t_shell *shell_info);

//SIG_FUNCTIONS.C
void		sighandler(int sig);
void		sigchecker(int sigint, int sigquit);
void		catchsignal(void);

//SPLIT_MS.C
char		**split_ms(char const *s, char c);
void		update_quote_state_str(const char *str, int *sq, int *dq, int i);
void		update_ints(char const *s, int *end, int *dq, int*sq);
void		update_position(int *end, int *start, char const *s, char c);
char		*create_ms_split_array(char *array, int *end, int *start, \
char const *s);

//TOKENIZER.C
void		create_tokens(t_shell *shell_info);
t_token		*create_single_token(t_shell *shell_info, int i);
t_token		*create_double_token(t_shell *shell_info, int i);
void		initialize_token(t_token *tok);

//UNSET.C
char		**ft_path_in_envmini(t_env_mini *env_mini);
void		run_unset(char *str, t_shell *shell_info);
void		free_env_node(t_env_mini *lnli);

//UTILS_DIRECTORY
void		token_add_back(t_token **first_token, t_token *new);
t_token		*token_last(t_token *token);
int			skip_whitespace(char *inpt, int i);
int			num_of_total_cmds(t_command *cur);
t_command	*get_last_cmd(t_command *cmd);
void		close_fds(t_shell *shell_info, t_command *cur);
void		close_io(t_command *cur);
bool		is_metacharacter(char c);
bool		is_ws(char c);
void		cmd_add_back(t_command **first_token, t_command *new);
int			handle_exit(int status);
bool		is_metacharacter_type(int i);
int			token_count(t_shell *shell_info);
bool		is_redir(int i);
bool		is_redir_pipe(t_token_type i);
bool		is_redir_pipe_char(char i);
bool		ft_is_builtin(char *str);
bool		quotes_even(char *input);
bool		is_double(t_shell *shell_info, int i);
void		finalise_node(t_shell *shell_info, t_command *cmd_node);
void		nullify_ints_four(int *sq, int *dq, int *i, int *counter);
void		reset(t_shell *shell_info);
bool		has_double_pipe(t_token *iter, int dq, int sq);
t_token		*double_pipe_case(t_shell *shell_info, t_token *iter);
bool		has_redir_twice(t_token *iter, int dq, int sq);
t_token		*twice_redir_case(t_shell *shell_info, t_token *iter);
char		*get_first_word(char *argv);
t_token		*create_word_token(t_shell *sh_i, int i);
void		proc_exit(int status, t_shell *shell_info);

//EXECUTION.C
void		handle_redir(t_shell *shell_info, t_command *cur);
void		execution_cases(t_shell *shell_info);
pid_t		exec_pipeline(t_shell *shell_info);
pid_t		exec_single_cmd(t_shell *shell_info, t_command	*cmd_to_exec);
void		pipe_handling(t_shell *shell_info, t_command *cur);
void		close_pipes(t_shell *shell_info);
void		execute_builtin(t_shell *shell_info, t_command *cur);
void		child_proccess(t_shell *shell_info, t_command *cmd_to_exec, \
char *full_path, char **paths_in_env);

//ERRORS
void		file_error(t_command *cmd_node);
void		heredoc_error(t_command *cmd_node);
void		cmd_error(t_command *cmd_node);
void		unexpected_token(t_shell *shell_info, char *flag);
void		quote_error(t_shell *shell_info);
void		env_error(char *cmd);

//EXPORT.C
t_env_mini	*ft_lstnew_envmini(char *name, char *value);
t_env_mini	*ft_lstlast_envmini(t_env_mini *lst);
void		run_export(char *str, t_shell *shell_info);
void		free_split_set_null(char **keywords);
void		free_set_null(char *str);

//EXPAND.C
int			is_al_num_udsc_c(char c);
int			ft_varname_len(char *str);
char		*ft_varvalue(int var_name_len, char *str, \
t_env_mini *env_mini);
char		*replace_exp(char *inpt, char *var_value, \
int var_name_len);
void		ft_expand(t_shell *shell_info);
void		replace_caret(t_shell *shell_info);

//FREES
void		free_tokens(t_token **shell_info);
void		free_cmd_list(t_command **cmds);
void		free_shell(t_shell *shell_info);
void		free_envmini(t_env_mini *env_mini);

//QUOTES
char		*quote_handler(t_token *iterate, t_token_type flag);
t_token		*skip_quoted_str(t_token *to_skip, t_token_type flag);
char		*rm_q_in_fullcmd(char *to_fix);

//BUILTIN_ARGS
char		*arg_for_export(t_token *cur);
t_token		*skip_tokens_of_builtin_arg(t_token *iterate);
t_token		*initialise_builtin_type_arg(t_command *cmd_node, t_token *iterate);

//REDIR.C
t_token		*set_redirections(t_command *cmd_node, t_token *iterate);
void		handle_heredoc(t_command *cmd_node, char *delimiter);
void		file_opener(t_command *cmd_node, int flag, char *file);

//WHITE_SPACE.C
char		*rm_starting_ws(char *string);
void		cpy_chars(char *str, int *i, int *j);
char		*multiple_ws_to_single(char	*str);
char		*ptr_ws(char *inpt);

//SYNTAX
void		syntax_error_check(t_shell *shell_info);
bool		syntax_error_at_start(t_token *iter);
void		syntax_error_at_start_msg(t_shell *shell_info, t_token *iter);

//LAST
void		nullify_ints_two(int *inside_sq, int *inside_dq);
char		*repl_exp_return(char *str_till_dollar, char *str_after_varname);
t_env_mini	*env_to_envmini_helper(t_env_mini *env_mini);
void		run_export_keyword_error(int *status, char *var_name, \
char *var_value, char *ptr);
void		cd_helper(t_shell *shell_info);

#endif
