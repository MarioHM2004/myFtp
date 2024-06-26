/*
** EPITECH PROJECT, 2024
** help.c
** File description:
** help socket
*/

#include "../include/server.h"

void error(const char *msg)
{
    printf("%s\n", msg);
    exit(84);
}

char *get_path()
{
    char *cwd = malloc(1024);

    if (getcwd(cwd, 1024) == NULL) {
        error("getcwd error");
    }
    return cwd;
    free(cwd);
}

void args_handling(server_t *server, int ac, char **av)
{
    if (av[1] && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myftp <port> <path>\n\
    <port>  is the port number on which the server socket listens\n\
    <path>  is the path to the home directory for the Anonymous user\n");
        exit(EXIT_SUCCESS);
    } else if (ac != 3) {
        error("usage: ./myftp <port> <path>\n\
    for more info: ./myftp -help");
    }
    init_path(av);
    server->path = get_path();
}
