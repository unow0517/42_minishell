################################################################################
#									CONSTANTS								   #
################################################################################
CC = cc
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
		freeing.c \
		freeing_extras.c \
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
		$(UTILS)/export_utils.c \
		$(UTILS)/expand_util.c \
		$(UTILS)/expand_util_2.c \
		$(UTILS)/last_extras.c \
		$(UTILS)/expand_replaces.c \
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
		$(UTILS)/quotes_one.c \
		$(UTILS)/syntax.c \
		$(UTILS)/exec_helper.c \
		$(UTILS)/tokenizer_utils.c

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
