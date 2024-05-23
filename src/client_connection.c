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
 
void send_msg_to_client(server_t *server, const char *msg)
{
    int length = 0;
 
    if (msg == NULL)
        return send_msg_to_client(server, "XXX null message :(");
    length = strlen(msg);
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
 
void client_connection(server_t *server, int client_socket)
{
    int bytes = 0;
    char *needle = "\r\n";
    char *found = NULL;
    server->client_socket = client_socket;
    server->client_response = calloc(MAX_BYTES, 1);
    if (server->client_response == NULL)
        error("malloc failed");
    bytes = read(server->client_socket, server->client_response, MAX_BYTES - 1);
    if (bytes <= 0) {
        if (bytes < 0)
            error("read failed");
        close(server->client_socket);
        FD_CLR(server->client_socket, &server->current_sockets);
        free(server->client_response);
        server->client_response = NULL;
    } else {
        found = strstr(server->client_response, needle);
        if (found == NULL)
            error("clrf not found");
        *found = '\0';
        command_parsing(server);
    }
}