SRC = utils.c input.c main.c struct.c actions.c threads.c
OBJS = ${SRC:.c=.o}

CC = cc
FLAGS = -g -Wall -Werror -Wextra #-fsanitize=thread

RM = rm -rf

NAME = philo

YELLOW = \033[33m
GREEN = \033[32m
RED = \033[31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)PHILO PROGRAM GENERATED$(RESET)"
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	@echo "$(YELLOW)COMPILING OBJECTS...$(RESET)"
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "$(RED)OBJECTS DELETED$(RESET)"
	$(RM) $(OBJS)

fclean: clean
	@echo "$(RED)PROGRAM DELETED$(RESET)"
	$(RM) $(NAME)

re: fclean all

.SILENT: 