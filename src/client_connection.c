/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server socket
*/

#include "../include/server.h"

void commands_handler(server_t *server, cmd_t *commands)
{
    init_is_logged(server);
    for (int i = 0; commands[i].cmd != NULL; i++) {
        if (strcmp(server->command_arr[0], commands[i].cmd) == 0) {
            return commands[i].fn(server, server->command_arr);
        }
    }
    return msg_client(server, get_messages(INVALID_COMMAND));
}

void client_commands(server_t *server)
{
    cmd_t commands[] = {
    {"USER", cmd_user},
    {"PASS", cmd_pass},
    {"QUIT", cmd_quit},
    {"PWD", cmd_pwd},
    {"CDUP", cmd_cdup},
    {"CWD", cmd_cwd},
    {"LIST", cmd_list},
    {"NOOP", cmd_noop},
    {"HELP", cmd_help},
    {"DELE", cmd_dele},
    {"PASV", cmd_pasv},
    {"RETR", cmd_retr},
    {"STOR", cmd_stor},
    {NULL, NULL}
    };

    commands_handler(server, commands);
}

void client_handler(server_t *server, char *found, char *needle, int bytes)
{
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

void client_connection(server_t *server, int client_socket)
{
    int bytes = 0;
    char *needle = "\r\n";
    char *found = NULL;

    server->client_socket = client_socket;
    server->client_response = calloc(MAX_BYTES, 1);
    if (server->client_response == NULL)
        error("malloc failed");
    bytes = read(server->client_socket,
        server->client_response, MAX_BYTES - 1);
    client_handler(server, found, needle, bytes);
}
