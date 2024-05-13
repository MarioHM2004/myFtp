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

void send_msg_to_client(server_s *server, char *msg)
{
    char *server_message = malloc(sizeof(char)*strlen(msg)+1);

    strcpy(server_message, msg);
    if (write(server->i, server_message, strlen(server_message)) == -1) {
        error("write failed");
    }
    free(server_message);
}

void client_commands(server_s *server)
{
    cmd_t commands[] = {
    {"USER", cmd_user},
    {"QUIT", cmd_quit},
    {NULL, NULL}
    };
    for (int i = 0; commands[i].cmd != NULL; i++) {
        if (strcmp(server->command_arr[0], commands[i].cmd) == 0) {
            return commands[i].fn(server, server->command_arr);
        }
    }
    return command_error(server, "500");
}

void client_connection(server_s *server)
{
    while(1) {
        server->client_response = malloc(MAX_BYTES);
        if (server->client_response == NULL) {
            error("malloc failed");
        }
        if (read(server->i, server->client_response, MAX_BYTES) == -1) {
            error("read failed");
        }
        char *needle = "\r\n";
        char *found = strstr(server->client_response, needle);

        if (found == NULL) {
            error("no newline found");
        }
        *found = '\0';
        command_parsing(server);
        free(server->client_response);
    }
}
