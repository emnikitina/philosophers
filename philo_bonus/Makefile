CC = gcc
FLAGS = -Wall -Wextra -Werror
SRCS = main.c\
	   life.c\
	   my_atoi.c\
	   utils.c

OBJ = $(SRCS:.c=.o)
RM = rm -f
NAME = philo_bonus

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) philo_bonus.h
	$(CC) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean:
	$(RM) $(NAME) $(OBJ)

re: fclean all
