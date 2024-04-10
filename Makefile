NAME = pipex
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -o

SRC = main.c parsing.c pipex.c \
		utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(NAME) $(SRC)
clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all