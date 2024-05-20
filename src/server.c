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

int create_server_socket(server_t *server, int port)
{
    struct sockaddr_in server_addr;

    server->server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (server->server_socket < 0)
        error("Socket creation failed");
    if (setsockopt(server->server_socket, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
        error("setsockopt(SO_REUSEADDR) failed");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server->server_socket, (struct sockaddr *)&server_addr,
        sizeof(server_addr)) == -1) {
        perror("bind");
    }
    printf("waiting for client connections...\n");
    listen(server->server_socket, 5);
    return server->server_socket;
}

void help_connection(server_t *server, int i)
{
    if (i == server->server_socket) {
        socklen_t addr_size = sizeof(server->client_addr);
        server->client_socket = accept(server->server_socket, (struct sockaddr*)&server->client_addr, &addr_size);
        if (server->client_socket < 0) {
            error("client error");
        }
        send_msg_to_client(server, "220 Service ready for new user.");
        printf("client connected\n");
        FD_SET(server->client_socket, &(server->current_sockets));
        } else {
        client_connection(server);
        FD_CLR(i, &(server->current_sockets));
    }
}

void connection_manager(server_t *server, int i)
{
    for (i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, &server->ready_sockets)) {
            help_connection(server, i);
        }
    }
}

void run_server(server_t *server)
{
    int i = 0;
    server->client_socket = 0;

    FD_ZERO(&server->current_sockets);
    FD_SET(server->server_socket, &server->current_sockets);
    while (1) {
        server->ready_sockets = server->current_sockets;
        if (select(FD_SETSIZE, &server->ready_sockets,
            NULL, NULL, NULL) < 0)
            error("select error");
        connection_manager(server, i);
    }
}
