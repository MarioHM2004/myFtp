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
#include "../include/server.h"

void cmd_user(server_s *server, char **args)
{
    char *username = args[1];

    if (username == NULL) {
        return command_error(server, "501");
    }
    if (strcmp(username, "Anonymous") == 0) {
        return send_msg_to_client(server, "331 User name okay, need password.\n");
    }
    return command_error(server, "530");
}

void cmd_quit(server_s *server, char **args)
{
    send_msg_to_client(server, "221 Closing client\n");
}

void command_error(server_s *server, char *number)
{
    char *fmt = "%s Error (RFC compliant)\n";
    dprintf(server->i, fmt, number);
}