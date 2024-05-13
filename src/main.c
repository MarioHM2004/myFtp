/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server socket
*/

#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/server.h"

int main(int ac, char **av)
{
    struct server_s *server = malloc(sizeof(server_s));

    usage_help(ac, av);
    server->server_socket = create_server_socket(server, atoi(av[1]));
    run_server(server);
    close(server->server_socket);
    free(server);
    return 0;
}
