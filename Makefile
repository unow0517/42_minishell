NAME = minishell
CC = gcc
SRC = errors.c quotes.c execution.c parsing.c inpt_handler.c freeing.c minishell.c inpt_functions.c history.c sig_functions.c pwd.c pipe.c echo.c cd.c env.c white_space.c tokenizer.c pipex_functions.c checks.c utils.c dollar_expand.c export.c unset.c backslash.c
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -rf
LIBFT_AR = Libft/libft.a
PRINTF_AR = ft_printf/libftprintf.a

all: $(LIBFT_AR) $(PRINTF_AR) $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT_AR) $(PRINTF_AR) -o $(NAME) -lreadline

#for wsl
# https://stackoverflow.com/questions/53507756/undefined-reference-to-readline-in-c-file-on-ubuntu-18-04-libreadline-dev-ins

$(LIBFT_AR):
	cd Libft && make

$(PRINTF_AR):
	cd ft_printf && make

clean:
	cd Libft && make clean
	cd ft_printf && make clean
	@$(RM) $(NAME)

fclean: clean
	@$(RM) $(LIBFT_AR)
	@$(RM) $(PRINTF_AR)
	@$(RM) $(NAME)

re: fclean all