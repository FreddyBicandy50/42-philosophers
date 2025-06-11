NAME = philo
INCLUDES = ./includes/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g  -I$(INCLUDES)
SRCS = main.c \
		src/init_table.c src/parsing.c \
		src/safety.c src/philo.c src/utils.c

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
clean:
	@clear
	rm -f $(OBJECTS)
fclean: clean
	@clear
	rm -f $(NAME)
re: fclean all clean

.PHONY: all clean fclean re