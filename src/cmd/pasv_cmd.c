/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <dirent.h>
#include "../../include/server.h"

int accept_data_connection(server_t *server)
{
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int accepted_data_socket = accept(server->data_socket,
        (struct sockaddr *)&client_addr, &addr_len);

    if (accepted_data_socket == -1) {
        error("Data connection accept failed");
        close(server->data_socket);
        server->data_socket = -1;
        return -1;
    }
    return accepted_data_socket;
}

int enter_passive_mode(int *port)
{
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in data_addr;

    if (data_socket == -1)
        error("Data socket creation failed");
    memset(&data_addr, 0, sizeof(data_addr));
    data_addr.sin_family = AF_INET;
    data_addr.sin_addr.s_addr = INADDR_ANY;
    for (;;) {
        *port = 1025 + rand() % (65535 - 1025);
        data_addr.sin_port = htons(*port);
        if (bind(data_socket,
            (struct sockaddr *)&data_addr, sizeof(data_addr)) == 0)
            break;
    }
    if (listen(data_socket, 1) == -1) {
        close(data_socket);
        error("Data socket listen failed");
    }
    return data_socket;
}

void get_local_ip_port(server_t *server, char *server_ip, int *port)
{
    struct sockaddr_in local_address;
    socklen_t address_length = sizeof(local_address);

    if (getsockname(server->server_socket,
            (struct sockaddr *)&local_address, &address_length) < 0) {
        perror("getsockname failed");
        close(server->data_socket);
        return;
    }
    if (inet_ntop(AF_INET,
            &(local_address.sin_addr), server_ip, sizeof(server_ip)) == NULL) {
        perror("inet_ntop failed");
        close(server->data_socket);
        return;
    }
}

void cmd_pasv(server_t *server, char **args)
{
    int port = 0;
    char server_ip[INET_ADDRSTRLEN];

    if (server->data_socket != -1) {
        close(server->data_socket);
        server->data_socket = -1;
    }
    server->data_socket = enter_passive_mode(&port);
    get_local_ip_port(server, server_ip, &port);
    build_response(server, server_ip, &port);
    server->accepted_data_socket = accept_data_connection(server);
    if (server->accepted_data_socket == -1) {
        msg_client(server, "425 Can't open data connection.");
        close(server->data_socket);
        server->data_socket = -1;
    }
}
