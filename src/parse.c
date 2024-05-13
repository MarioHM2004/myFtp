/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** command input parser
*/

#include "../include/server.h"
#include <stdlib.h>
#include <string.h>

void command_parsing(server_s *server)
{
    int max_alloc = 1;
    char *data = server->client_response;
    char *end = data + strlen(data) - 1;
    char *current = NULL;
    int len = 0;

    while (*data == ' ') {
        data++;
    }
    while (*end == ' ') {
        *end = '\0';
        end--;
    }
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
    server->command_arr = malloc(sizeof(char *) * max_alloc);
    if (server->command_arr == NULL) {
        error("malloc failed");
    }
    current = data;
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
    client_commands(server);
}
