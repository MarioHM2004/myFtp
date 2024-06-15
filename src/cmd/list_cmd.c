/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/


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

void check_errors(server_t *server, char **args)
{
    size_t length = 0;

    if (!server->is_logged)
        return msg_client(server,
            get_messages(NOT_LOGGED_IN));
    for (int i = 0; args[i] != NULL; i++)
        length++;
    if (length > 2)
        return msg_client(server,
            get_messages(INVALID_ARGUMENTS));
}

void handle_list_command(server_t *server, char **args)
{
    DIR *dir;
    char *path = NULL;
    char *listing = NULL;

    check_errors(server, args);
    path = (args[1] ? args[1] : server->path);
    dir = opendir(path);
    if (dir == NULL)
        return msg_client(server,
            get_messages(WRONG_PATH));
    listing = reader_conditions(server, dir, args);
    msg_client(server, "150 Here comes the directory listing.");
    server->accepted_data_socket = accept_data_connection(server);
    msg_data_socket(server->accepted_data_socket, listing);
    free(listing);
}

void cleanup_data_connections(server_t *server)
{
    close(server->accepted_data_socket);
    server->accepted_data_socket = -1;
    msg_client(server, "226 Directory send OK.");
}

void cmd_list(server_t *server, char **args)
{
    handle_list_command(server, args);
    cleanup_data_connections(server);
}
