/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server socket
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/server.h"

int create_server_socket(server_s *server, int port)
{
    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    if (server->server_socket == -1)
        error("Socket creation failed");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server->server_socket, (struct sockaddr *)&server_addr,
        sizeof(server_addr)) == -1) {
        error("Binding failed");
    }
    printf("waiting for client connections...\n");
    listen(server->server_socket, 5);
    return server->server_socket;
}

void help_connection(server_s *server)
{
    if (server->i == server->server_socket) {
        server->client_socket = accept(server->server_socket, NULL, NULL);
        printf("client connected\n");
        FD_SET(server->client_socket, &(server->current_sockets));
    } else {
        client_connection(server);
        FD_CLR(server->i, &(server->current_sockets));
    }
}

void connection_manager(server_s *server)
{
    for (server->i = 0; server->i < FD_SETSIZE; server->i++) {
        if (FD_ISSET(server->i, &server->ready_sockets)) {
            help_connection(server);
        }
    }
}

void run_server(server_s *server)
{
    server->client_socket = 0;

    FD_ZERO(&server->current_sockets);
    FD_SET(server->server_socket, &server->current_sockets);
    while (1) {
        server->ready_sockets = server->current_sockets;
        if (select(FD_SETSIZE, &server->ready_sockets,
            NULL, NULL, NULL) < 0)
            error("select error");
        connection_manager(server);
    }
}
