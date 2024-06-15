/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/

#include "../../include/server.h"

void cmd_noop(server_t *server, char **args)
{
    if (!server->is_logged)
        return msg_client(server, get_messages(NOT_LOGGED_IN));
    msg_client(server, "200 Command okay.");
}
