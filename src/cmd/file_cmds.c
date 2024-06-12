/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <dirent.h>
#include "../../include/server.h"

char *reader_conditions(server_t *server, DIR *dir, char **args)
{
    struct dirent *entry;
    char *listing = malloc(256);


    while (1) {
        entry = readdir(dir);
        if (!entry)
            break;
        if (strcmp(entry->d_name, ".") == 0
            || strcmp(entry->d_name, "..") == 0
            || entry->d_name[0] == '.')
            continue;
        strcat(listing, entry->d_name);
        strcat(listing, "\r\n");
    }
    closedir(dir);
    return listing;
}

void cmd_list(server_t *server, char **args)
{
    size_t length = 0;
    char *path = NULL;
    DIR *dir;

    if (!server->is_logged)
        return msg_client(server, get_messages(NOT_LOGGED_IN));
    for (int i = 0; args[i] != NULL; i++)
        length++;
    if (length > 2)
        return msg_client(server, get_messages(INVALID_ARGUMENTS));
    int accepted_data_socket = accept_data_connection(server);
    if (accepted_data_socket == -1) {
        msg_client(server, "425 Can't open data connection.");
        close(server->data_socket);
        server->data_socket = -1;
    } else {
        path = (args[1] ? args[1] : server->path);
        dir = opendir(path);
        if (dir == NULL)
            return msg_client(server, get_messages(WRONG_PATH));
        char *listing = reader_conditions(server, dir, args);
        msg_client(server, "150 Here comes the directory listing.");
        msg_data_socket(accepted_data_socket, listing);
        close(accepted_data_socket);
        close(server->data_socket);
        server->data_socket = -1;
        msg_client(server, "226 Directory send OK.");
        free(listing);
    }
}
