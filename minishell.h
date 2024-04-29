/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 19:13:36 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/29 13:22:17 by yowoo            ###   ########.fr       */
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

# define SHE 0
# define DFL 1
# define IGN 2

// typedef struct s_mini
// {
// 	char	*cwd;
// }	t_mini;

//added by thalia
typedef enum s_type
{
	WORD,
	PIPE,
	S_QUOTE,
	D_QUOTE,
	S_LESS,
	S_MORE,
	D_LESS,
	D_MORE
}	t_type;

typedef struct s_token //token, not token
{
	char			*input;
	int				len;
	int				i;
	t_type			token_type;
	struct s_token	*next;
} t_token;

typedef struct s_shell
{
	int		argc;
	char	**env;
	char	*cwd;
	t_token	**first_token_node;
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

// //PIPEX_FUNCTIONS.C
char	*get_first_word(char *argv);
void	handle_error(char *str);
void	free_split_thalia(char **str);

//MINISHELL.C
void	inpt_handler(char *prompt, char **argv, char **env, t_shell *info);
void	initialise_basics(int argc, char **env, t_shell *info);
//int	main(int argc, char **argv, char **env);

//SET_NODES.C
void	input_types(char *inpt, t_shell *info, t_token *first_token);
int		set_token_word(char *inpt, int i, t_token *token);
int		set_token_not_word(char *inpt, int i, t_token *token);

//UTILS
void	token_add_back(t_token **first_token, t_token *new);
t_token	*token_last(t_token *token);
int		skip_whitespace(char *inpt, int i);

//FREES
void	free_small_linked(t_shell *shell_info);

#endif
