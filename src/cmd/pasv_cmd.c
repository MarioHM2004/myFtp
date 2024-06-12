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

int accept_data_connection(server_t *server) {
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int accepted_data_socket = accept(server->data_socket, (struct sockaddr *)&client_addr, &addr_len);
    if (accepted_data_socket == -1) {
        perror("Data connection accept failed");
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
        if (bind(data_socket, (struct sockaddr *)&data_addr, sizeof(data_addr)) == 0)
            break;
    }
    if (listen(data_socket, 1) == -1) {
        close(data_socket);
        error("Data socket listen failed");
    }
    return data_socket;
}

void cmd_pasv(server_t *server, char **args)
{
    int port = 0;
    char server_ip[INET_ADDRSTRLEN];
    unsigned int h1, h2, h3, h4;
    struct sockaddr_in local_address;
    int p2 = 0;
    int p1 = 0;
    char response[256];
    socklen_t address_length = sizeof(local_address);

    server->data_socket = enter_passive_mode(&port);
    if (getsockname(server->server_socket, (struct sockaddr *)&local_address, &address_length) < 0) {
        perror("getsockname failed");
        close(server->data_socket);
        return;
    }
    if (inet_ntop(AF_INET, &(local_address.sin_addr), server_ip, sizeof(server_ip)) == NULL) {
        perror("inet_ntop failed");
        close(server->data_socket);
        return;
    }
    p1 = port / 256;
    p2 = port % 256;
    sscanf(server_ip, "%u.%u.%u.%u", &h1, &h2, &h3, &h4);
    snprintf(response, sizeof(response),
        "227 Entering Passive Mode (%u,%u,%u,%u,%d,%d).", h1, h2, h3, h4, p1, p2);
    msg_client(server, response);
}
