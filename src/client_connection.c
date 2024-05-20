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
#include "../include/server.h"

void send_msg_to_client(server_t *server, const char *msg)
{
    if (msg == NULL) {
        return send_msg_to_client(server, "XXX null message :(");
    }

    int length = strlen(msg);
    write(server->client_socket, msg, length);
    write(server->client_socket, "\r\n", 2);
}

void client_commands(server_t *server)
{
    cmd_t commands[] = {
    {"USER", cmd_user},
    {"PASS", cmd_pass},
    {"QUIT", cmd_quit},
    {"PWD", cmd_pwd},
    {NULL, NULL}
    };
    for (int i = 0; commands[i].cmd != NULL; i++) {
        if (strcmp(server->command_arr[0], commands[i].cmd) == 0) {
            return commands[i].fn(server, server->command_arr);
        }
    }
    return send_msg_to_client(server, message(INVALID_COMMAND));
}

void client_connection(server_t *server)
{
    while (1) {
        server->client_response = malloc(MAX_BYTES);
        if (server->client_response == NULL) {
            error("malloc failed");
        }
        if (read(server->client_socket, server->client_response, MAX_BYTES) == -1) {
            error("read failed");
        }
        char *needle = "\r\n";
        char *found = strstr(server->client_response, needle);
        if (found == NULL) {
            error("clrf not found");
        }
        *found = '\0';
        command_parsing(server);
    }
}
