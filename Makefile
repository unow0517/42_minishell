# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 17:57:56 by yowoo             #+#    #+#              #
#    Updated: 2024/04/19 17:09:37 by yowoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
SRC = minishell.c inpt_functions.c history.c sig_functions.c pwd.c pipe.c echo.c cd.c
CC_FLAGS = -Wall -Wextra -Werror -lreadline
RM = rm -rf
LIBFT_AR = Libft/libft.a
PRINTF_AR = ft_printf/libftprintf.a
all: $(NAME)

$(NAME):
	cd Libft && make
	cd ft_printf && make
	@$(CC) $(CC_FLAGS) $(SRC) $(LIBFT_AR) $(PRINTF_AR) -o $(NAME)

clean:
	cd Libft && make clean
	cd ft_printf && make clean
	@$(RM) $(NAME)

fclean: clean
	@$(RM) $(LIBFT_AR)
	@$(RM) $(PRINTF_AR)
	@$(RM) $(NAME)

re: fclean all