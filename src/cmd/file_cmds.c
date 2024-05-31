/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/

#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <dirent.h>
#include "../../include/server.h"

void cmd_dele(server_t *server, char **args)
{
    size_t length = 0;

    for (int i = 0; args[i] != NULL; i++)
        length++;
    if (!server->is_logged)
        return msg_client(server, get_messages(NOT_LOGGED_IN));
    if (length != 2)
        return msg_client(server, get_messages(INVALID_ARGUMENTS));
    if (unlink(args[1]) == 0)
        msg_client(server, "250 Requested file action okay, completed.");
    else
        msg_client(server, get_messages(INVALID_FILE));
}
