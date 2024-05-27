################################################################################
#									CONSTANTS								   #
################################################################################
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBS = libft.h minishell.h
LIBFT_PATH = ./Libft
LIBFT := $(LIBFT_PATH)/libft.a
LDFLAGS = -L $(LIBFT_PATH) -lft -lreadline

NAME = minishell

################################################################################
#									MAIN PART								   #
################################################################################

SRCS =	awk.c \
		awk_utils.c \
		builtin_args.c \
		cd.c \
		checks.c \
		echo.c \
		env.c \
		errors.c \
		execution.c \
		expand.c \
		export.c \
		freeing.c \
		history.c \
		inpt_functions.c \
		inpt_handler.c \
		minishell.c \
		parsing.c \
		parsing_cases.c \
		parsing_helper.c \
		pipe.c \
		pipex_functions.c \
		pwd.c \
		quotes.c \
		redir.c \
		sig_functions.c \
		split_ms.c \
		tokenizer.c \
		unset.c \
		utils.c \
		white_space.c

OBJ = $(SRCS:.c=.o)

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

$(OBJ) : %.o : %.c
	@$(CC) -c $(CFLAGS) -I$(LIBFT_PATH) $< -o $@

clean :
	@echo "Removing $(OBJ)"
	@rm -f $(OBJ)
	@make -C $(LIBFT_PATH) clean

fclean : clean
	@echo "Removing $(NAME)"
	@rm -f $(NAME)
	@make -C $(LIBFT_PATH) fclean

re : fclean all

################################################################################
#									LIBFT									   #
################################################################################

$(LIBFT):
	@echo "Building libft..."
	@make -C $(LIBFT_PATH) --no-print-directory

.PHONY :
	all clean fclean re
