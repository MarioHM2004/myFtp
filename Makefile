##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC	=	./src/main.c						\
		./src/server/server.c				\
		./src/help.c						\
		./src/server/client_connection.c	\

OBJ	=	$(SRC:.c=.o)

FLAG	=	-Wall -Werror -o

NAME	=	myftp

all:	$(NAME)

$(NAME):	$(OBJ)
		gcc $(FLAG) $(NAME) $(SRC)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
