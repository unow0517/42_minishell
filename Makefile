# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 17:57:56 by yowoo             #+#    #+#              #
#    Updated: 2024/04/27 22:13:14 by tsimitop         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
SRC = loop.c freeing.c minishell.c inpt_functions.c history.c sig_functions.c pwd.c pipe.c echo.c cd.c env.c white_space.c set_nodes.c pipex_functions.c checks.c utils.c
CC_FLAGS = -Wall -Wextra -Werror -lreadline #-fsanitize=address
RM = rm -rf
LIBFT_AR = Libft/libft.a
PRINTF_AR = ft_printf/libftprintf.a

all: $(LIBFT_AR) $(PRINTF_AR) $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CC_FLAGS) $(SRC) $(LIBFT_AR) $(PRINTF_AR) -o $(NAME)

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