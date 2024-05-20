/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** command input parser
*/

#include "../include/server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void strip_spaces(char *data)
{
    while (*data == ' ') {
        data++;
    }
}

void trim_trailing_spaces(char *data)
{
    char *end = data + strlen(data) - 1;
    while (*end == ' ') {
        *end = '\0';
        end--;
    }
}

int count_tokens(char *data)
{
    int max_alloc = 1;
    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == ' ') {
            while (data[i] == ' ') {
                i++;
            }
            if (data[i] == '\0') {
                break;
            }
            max_alloc++;
        }
    }
    return max_alloc;
}

void allocate_command_array(server_t *server, int max_alloc)
{
    server->command_arr = malloc(sizeof(char *) * max_alloc + 1);
    if (server->command_arr == NULL) {
        error("malloc failed");
    }
}

void extract_tokens(server_t *server, char *data, int max_alloc)
{
    char *current = data;
    int len = 0;
    for (int i = 0; i < max_alloc; i++) {
        char *next = strchr(current, ' ');
        if (next == NULL) {
            next = strchr(current, '\0');
        }
        len = next - current;
        server->command_arr[i] = malloc(len + 1);
        if (server->command_arr[i] == NULL) {
            error("malloc failed");
        }
        strncpy(server->command_arr[i], current, len);
        server->command_arr[i][len] = '\0';
        while (*next == ' ') {
            next++;
        }
        current = next;
    }
    server->command_arr[max_alloc] = NULL;
}

void command_parsing(server_t *server)
{
    char *data = server->client_response;
    strip_spaces(data);
    trim_trailing_spaces(data);
    int max_alloc = count_tokens(data);
    allocate_command_array(server, max_alloc);
    extract_tokens(server, data, max_alloc);
    client_commands(server);
}
