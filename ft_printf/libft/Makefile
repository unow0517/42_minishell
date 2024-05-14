CC := cc

CFLAGS := -Wall -Werror -Wextra

CFILES = ft_strlen.c

OFILES = $(CFILES:.c=.o)

NAME = libft.a

#target: prerequisites
#	command
#	command...
#prerequisites(=dependencies) are file names which should exists to run target 

#[make] will run [all] automatically since it is the first target

all: $(NAME)

#make libft.a will make an archive(library) with OFILES
$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

%.o: %c 
	$(CC) -c $(CFLAGS) -o $(OFILES) $(CFILES)

# $@ = target name
# $< = The name of the first prerequisite
# -c = Prevents the preprocessor from removing comments, except those on the preprocessing directive lines.
# -o = make obj file
# #^ = output all prerequisities

#[make clean] will remove all OBJ files
clean:
	rm -f $(OFILES)

#it first run [make clean], then remove [libft.a]
fclean: clean
	rm -f $(NAME)

#rebuild, first it delete all obj files and library with [fclean] and build 
re: fclean all

#libft.a should be generated at the end 

bonus: $(BOFILES)
	ar rcs $(NAME) $(BOFILES)