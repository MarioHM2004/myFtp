/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server socket
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../../include/server.h"

char *next_is_space(char *next)
{
    while (*next == ' ') {
        next++;
    }
    return next;
}

void extract_tokens(server_t *server, char *data, int max_alloc)
{
    char *current = data;
    int len = 0;
    char *next = NULL;

    for (int i = 0; i < max_alloc; i++) {
        next = strchr(current, ' ');
        if (next == NULL)
            next = strchr(current, '\0');
        len = next - current;
        server->command_arr[i] = malloc(len + 1);
        if (server->command_arr[i] == NULL)
            error("malloc failed");
        strncpy(server->command_arr[i], current, len);
        server->command_arr[i][len] = '\0';
        next = next_is_space(next);
        current = next;
    }
    server->command_arr[max_alloc] = NULL;
}

void allocate_command_array(server_t *server, int max_alloc)
{
    server->command_arr = malloc(sizeof(char *) * max_alloc + 1);
    if (server->command_arr == NULL) {
        error("malloc failed");
    }
}

void command_parsing(server_t *server)
{
    char *data = server->client_response;
    int max_alloc = 0;

    strip_spaces(data);
    trim_trailing_spaces(data);
    max_alloc = count_tokens(data);
    allocate_command_array(server, max_alloc);
    extract_tokens(server, data, max_alloc);
    client_commands(server);
}
