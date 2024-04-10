NAME = pipex
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g

SRC = main.c parsing.c pipex.c \
		utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(SRC) -o $(NAME) 
clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all