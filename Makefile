##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC	=	./src/main.c				\
		./src/server.c				\
		./src/help.c				\
		./src/client_connection.c	\
		./src/cmd.c					\
		./src/parse.c				\

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
