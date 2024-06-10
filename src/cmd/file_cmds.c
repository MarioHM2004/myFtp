/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/

#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <dirent.h>
#include "../../include/server.h"

void reader_conditions(server_t *server, DIR *dir)
{
    struct dirent *entry;
    msg_client(server, "150 File status okay; about to open data connection.");
    while (1) {
        entry = readdir(dir);
        if (!entry)
            break;
        if (strcmp(entry->d_name, ".") == 0
            || strcmp(entry->d_name, "..") == 0
            || entry->d_name[0] == '.')
            continue;
        msg_client(server, entry->d_name);
    }
    msg_client(server, "226 Closing data connection.");
}

void cmd_list(server_t *server, char **args)
{
    size_t length = 0;
    DIR *dir;
    char *path = NULL;

    if (!server->is_logged)
        return msg_client(server, get_messages(NOT_LOGGED_IN));
    for (int i = 0; args[i] != NULL; i++)
        length++;
    if (length > 2)
        return msg_client(server, get_messages(INVALID_ARGUMENTS));
    path = (args[1] ? args[1] : server->path);
    dir = opendir(path);
    if (dir == NULL)
        return msg_client(server, get_messages(WRONG_PATH));
    reader_conditions(server, dir);
    closedir(dir);
}
