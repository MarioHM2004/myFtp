##
## EPITECH PROJECT, 2024
## makefile
## File description:
## makefile
##

SRC	=	./src/main.c					\
		./src/server.c					\
		./src/help.c					\
		./src/client_connection.c		\
		./src/cmd/directory_cmd.c		\
		./src/cmd/login_cmd.c			\
		./src/cmd/quit_cmd.c			\
		./src/cmd/list_cmd.c			\
		./src/cmd/pasv_cmd.c			\
		./src/cmd/dele_cmd.c			\
		./src/cmd/retr_cmd.c			\
		./src/cmd/stor_cmd.c			\
		./src/cmd/noop_cmd.c			\
		./src/cmd/help_cmd.c			\
		./src/init.c					\
		./src/messages.c				\
		./src/parser/command_parser.c	\
		./src/parser/string_utils.c		\
		./src/parser/count_tokens.c		\

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
