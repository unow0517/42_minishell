# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/12 17:57:56 by yowoo             #+#    #+#              #
#    Updated: 2024/05/11 14:49:39 by yowoo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
SRC = execution.c parsing.c input_handler.c freeing.c minishell.c inpt_functions.c history.c sig_functions.c pwd.c echo.c cd.c env.c white_space.c tokenizer.c pipe.c pipex_functions.c checks.c dollar_expand.c utils.c export.c unset.c
CFLAGS = -Wall -Wextra -Werror -g -lreadline #-fsanitize=address
RM = rm -rf
LIBFT_AR = Libft/libft.a
PRINTF_AR = ft_printf/libftprintf.a

all: $(LIBFT_AR) $(PRINTF_AR) $(NAME)

$(NAME): $(SRC)
	@$(CC) $(CFLAGS) $(SRC) $(LIBFT_AR) $(PRINTF_AR) -o $(NAME)

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