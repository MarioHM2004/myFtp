/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server socket
*/

#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/include.h"

int main(int ac, char **av)
{
    int server_socket = 0;

    usage_help(ac, av);
    server_socket = create_server_socket(atoi(av[1]));
    run_server(server_socket);
    close(server_socket);
    return 0;
}
