/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server socket
*/

#include "../include/server.h"

int main(int ac, char **av)
{
    server_t *server = malloc(sizeof(server_t));

    server->port = atoi(av[1]);
    init_users(server);
    args_handling(server, ac, av);
    server->server_socket = create_server_socket(server);
    run_server(server);
    close(server->server_socket);
    free(server->users);
    free(server);
    return 0;
}
