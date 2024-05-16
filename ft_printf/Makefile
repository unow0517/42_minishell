CC := cc

CFLAGS := -Wall -Werror -Wextra

CFILES = ft_printf.c ft_printf_c.c ft_printf_int.c ft_printf_s.c ft_printf_p.c ft_printf_int.c ft_printf_u.c ft_printf_x.c ft_subfns_1.c ft_subfns_2.c ft_specifiers.c libft/ft_strlen.c

OFILES = $(CFILES:.c=.o)

NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all