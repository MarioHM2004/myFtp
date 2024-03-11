##
## EPITECH PROJECT, 2024
## NanoTekSpice
## File description:
## Makefile
##

SRC	=	./src/server/server.c				\
		./src/help.c						\

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
