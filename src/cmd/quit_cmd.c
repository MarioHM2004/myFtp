/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "../../include/server.h"

void cmd_quit(server_t *server, char **args)
{
    size_t length = 0;

    for (int i = 0; args[i] != NULL; i++) {
        length++;
    }
    if (length != 1) {
        return msg_client(server, get_messages(INVALID_ARGUMENTS));
    }
    return msg_client(server, "221 Service closing control connection.");
}

void cmd_noop(server_t *server, char **args)
{
    if (!server->is_logged)
        return msg_client(server, get_messages(NOT_LOGGED_IN));
    msg_client(server, "200 Command okay.");
}
