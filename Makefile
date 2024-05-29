################################################################################
#									CONSTANTS								   #
################################################################################
CC = cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LIBS = libft.h minishell.h
LIBFT_PATH = ./Libft
LIBFT := $(LIBFT_PATH)/libft.a
LDFLAGS = -L $(LIBFT_PATH) -lft -lreadline
UTILS = ./utils

NAME = minishell

################################################################################
#									MAIN PART								   #
################################################################################

SRCS =	awk.c \
		cd.c \
		checks.c \
		echo.c \
		env.c \
		errors.c \
		execution.c \
		expand.c \
		export.c \
		export_utils.c \
		freeing.c \
		history.c \
		inpt_functions.c \
		inpt_handler.c \
		minishell.c \
		parsing.c \
		parsing_cases.c \
		parsing_helper.c \
		pipe.c \
		pwd.c \
		redir.c \
		sig_functions.c \
		tokenizer.c \
		unset.c \
		white_space.c \
		expand_util.c \
		expand_util_2.c \
		expand_replaces.c \
		syntax.c \
		$(UTILS)/awk_utils.c \
		$(UTILS)/builtin_args.c \
		$(UTILS)/utils.c \
		$(UTILS)/linked_lists.c \
		$(UTILS)/if_cases.c \
		$(UTILS)/if_cases_one.c \
		$(UTILS)/if_cases_two.c \
		$(UTILS)/redir_quote.c \
		$(UTILS)/close_exit.c \
		$(UTILS)/cmd_utils.c \
		$(UTILS)/split_ms.c \
		$(UTILS)/split_helper.c \
		$(UTILS)/quotes.c \
		$(UTILS)/quotes_one.c

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
