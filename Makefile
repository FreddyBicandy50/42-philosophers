NAME = philo
BONUS = philo_bonus

INCLUDES = ./includes/

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g  -I$(INCLUDES)
CFLAGS_BONUS = -Wall -Wextra -Werror -g  -I ../bonus/includes

SRCS = main.c \
		src/init_table.c src/parsing.c \
		src/safety.c src/philo.c src/utils.c \
		src/manage.c

BSRCS = ../bonus/main.c \
		../bonus/src/init_table.c \
		../bonus/src/parsing.c \
		../bonus/src/safety.c \
		../bonus/src/philo.c \
		../bonus/src/utils.c \
		../bonus/src/manage.c

OBJECTS = $(SRCS:.c=.o)
BOBJECTS = $(BSRCS:.c=.o)


all: $(NAME)
bonus: $(BONUS)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

$(BONUS): $(BOBJECTS)
	$(CC) $(CFLAGS_BONUS) $(BOBJECTS) -o $(BONUS)

clean:
	rm -f $(OBJECTS) $(BOBJECTS)
fclean: clean
	rm -f $(NAME) $(BONUS)
re: fclean all clean

.PHONY: all clean fclean re