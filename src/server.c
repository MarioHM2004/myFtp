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
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../include/server.h"

int create_server_socket(server_t *server)
{
    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->server_socket < 0)
        error("Socket creation failed");
    if (setsockopt(server->server_socket, SOL_SOCKET,
        SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        error("setsockopt(SO_REUSEADDR) failed");
    server->server_addr.sin_family = AF_INET;
    server->server_addr.sin_port = htons(server->port);
    server->server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server->server_socket, (struct sockaddr *)&server->server_addr,
        sizeof(server->server_addr)) == -1) {
        perror("bind");
    }
    printf("waiting for client connections...\n");
    listen(server->server_socket, 5);
    return server->server_socket;
}

void new_client(server_t *server)
{
    socklen_t addr_size = sizeof(server->client_addr);
    int new_socket = accept(server->server_socket,
        (struct sockaddr *)&server->client_addr, &addr_size);

    if (new_socket < 0)
        error("accept error");
    printf("New client connected\n");
    server->client_socket = new_socket;
    msg_client(server, "220 Service ready for new user.");
    FD_SET(new_socket, &server->current_sockets);
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (server->client_sockets[i] == 0) {
            server->client_sockets[i] = new_socket;
            break;
        }
    }
}

void client_activity(server_t *server)
{
    int client_socket = 0;

    for (int i = 0; i < FD_SETSIZE; i++) {
        client_socket = server->client_sockets[i];
        if (client_socket > 0
            && FD_ISSET(client_socket, &server->ready_sockets))
            client_connection(server, client_socket);
    }
}

void run_server(server_t *server)
{
    FD_ZERO(&server->current_sockets);
    FD_SET(server->server_socket, &server->current_sockets);
    for (int i = 0; i < FD_SETSIZE; ++i) {
        server->client_sockets[i] = 0;
    }
    while (1) {
        server->ready_sockets = server->current_sockets;
        if (select(FD_SETSIZE, &server->ready_sockets,
            NULL, NULL, NULL) < 0)
            error("select error");
        if (FD_ISSET(server->server_socket, &server->ready_sockets))
            new_client(server);
        client_activity(server);
    }
}
