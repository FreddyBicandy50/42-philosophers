NAME = philo
INCLUDES = ./src/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g  -I$(INCLUDES)
SRCS = main.c \
        src/init_table.c \

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re