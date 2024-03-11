/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server socket
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../../include/include.h"

int create_server_socket(int port)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        error("Socket creation failed");
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        error("Binding failed");
    }
    printf("waiting for client connections...\n");
    listen(server_socket, 5);
    return server_socket;
}

void client_connection(int client_socket)
{
    char *message = "Hello World!!!\n";
    char *server_message = malloc(sizeof(char)*strlen(message) + 1);
    strcpy(server_message, message);
    send(client_socket, server_message, strlen(server_message)+1, 0);
    close(client_socket);
    free(server_message);
}

void run_server(int server_socket)
{
    fd_set current_sockets, ready_sockets;
    FD_ZERO(&current_sockets);
    FD_SET(server_socket, &current_sockets);

    while (1) {
        ready_sockets = current_sockets;

        if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0) 
            error("select error");

        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &ready_sockets)) {
                if (i == server_socket) {
                    int client_socket = accept(server_socket, NULL, NULL);
                    printf("client connected\n");
                    FD_SET(client_socket, &current_sockets);
                } else {
                    client_connection(i);
                    FD_CLR(i, &current_sockets);
                }
            }
        }
    }
}

int main(int ac, char **av)
{
    usage_help(ac, av);
    int server_socket = create_server_socket(atoi(av[1]));
    run_server(server_socket);
    close(server_socket);
    return 0;
}
