# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsimitop <tsimitop@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/13 20:13:13 by tsimitop          #+#    #+#              #
#    Updated: 2024/05/13 16:14:36 by tsimitop         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
PRINTF_PATH = ft_printf/
GNL_PATH = get_next_line/

SRC = ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_memset.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_tolower.c ft_toupper.c \
ft_bzero.c ft_memcpy.c ft_memmove.c ft_strchr.c ft_strrchr.c ft_strncmp.c \
ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
ft_atoll.c

SRC_PRINTF = $(PRINTF_PATH)/ft_printf.c $(PRINTF_PATH)/ft_putstr_fd.c \
$(PRINTF_PATH)/ft_putnbr_fd.c $(PRINTF_PATH)/ft_putchar_fd.c \
$(PRINTF_PATH)/ft_puthexlow_fd.c $(PRINTF_PATH)/ft_puthexup_fd.c \
$(PRINTF_PATH)/ft_putunsign_fd.c $(PRINTF_PATH)/ft_putptr_fd.c

SRC_GNL = $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c

OBJ_DIR = objects/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

OBJ_PRINTF = $(addprefix $(OBJ_DIR), $(notdir $(SRC_PRINTF:.c=.o)))

OBJ_GNL = $(addprefix $(OBJ_DIR), $(notdir $(SRC_GNL:.c=.o)))

all : $(NAME)

$(NAME): $(OBJ) $(OBJ_PRINTF) $(OBJ_GNL)
	@ar rc $(NAME) $(OBJ) $(OBJ_PRINTF) $(OBJ_GNL)

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(PRINTF_PATH)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(GNL_PATH)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@echo "Removing $(NAME)"
	@rm -f $(NAME)

re : fclean all
