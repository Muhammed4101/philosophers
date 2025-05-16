NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c init.c utils.c simulation.c actions.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re