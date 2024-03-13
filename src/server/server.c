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
#include "../../include/include.h"

int create_server_socket(int port)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;

    if (server_socket == -1)
        error("Socket creation failed");
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_socket, (struct sockaddr *)&server_addr,
        sizeof(server_addr)) == -1) {
        error("Binding failed");
    }
    printf("waiting for client connections...\n");
    listen(server_socket, 5);
    return server_socket;
}

void help_connection(int i, int server_socket,
    int client_socket, fd_set *current_sockets)
{
    if (i == server_socket) {
        client_socket = accept(server_socket, NULL, NULL);
        printf("client connected\n");
        FD_SET(client_socket, current_sockets);
    } else {
        client_connection(i);
        FD_CLR(i, current_sockets);
    }
}

void connection_manager(int server_socket, int client_socket,
    fd_set *current_sockets, fd_set *ready_sockets)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (FD_ISSET(i, ready_sockets)) {
            help_connection(i, server_socket, client_socket, current_sockets);
        }
    }
}

void run_server(int server_socket)
{
    int client_socket = 0;
    fd_set current_sockets;
    fd_set ready_sockets;

    FD_ZERO(&current_sockets);
    FD_SET(server_socket, &current_sockets);
    while (1) {
        ready_sockets = current_sockets;
        if (select(FD_SETSIZE, &ready_sockets,
            NULL, NULL, NULL) < 0)
            error("select error");
        connection_manager(server_socket, client_socket,
            &current_sockets, &ready_sockets);
    }
}
