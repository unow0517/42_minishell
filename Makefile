################################################################################
#									CONSTANTS								   #
################################################################################
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBS = libft.h minishell.h
LIBFT_PATH = ./Libft
LIBFT := $(LIBFT_PATH)/libft.a
LDFLAGS = -L $(LIBFT_PATH) -lft -lreadline

NAME = minishell

################################################################################
#									MAIN PART								   #
################################################################################

SRCS =	cd.c\
		echo.c\
		freeing.c\
		inpt_handler.c\
		pipe.c\
		tokenizer.c\
		unset.c\
		checks.c\
		env.c\
		history.c\
		minishell.c\
		pipex_functions.c\
		sig_functions.c\
		utils.c\
		dollar_expand.c\
		execution.c\
		inpt_functions.c\
		parsing.c\
		pwd.c\
		tokens.c\
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
