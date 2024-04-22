SRC = utils.c input.c main.c struct.c
OBJS = ${SRC:.c=.o}
CC = cc
FLAGS = -g -Wall -Werror -Wextra -pthread -fsanitize=thread
RM = rm -rf
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all