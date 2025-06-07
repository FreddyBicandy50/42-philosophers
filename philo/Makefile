NAME = philo
INCLUDES = ./includes/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g  -I$(INCLUDES)
SRCS = main.c \
		src/init_table.c src/logistics.c src/parsing.c \
		src/system.c

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
clean:
	rm -f $(OBJECTS)
fclean: clean
	@clear
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re