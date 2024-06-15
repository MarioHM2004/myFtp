/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/

#include "../../include/server.h"

void cmd_help(server_t *server, char **args)
{
    msg_client(server, "214 Help message.");
    msg_client(server, "USER\tPASS\tCWD\tCDUP");
    msg_client(server, "QUIT\tPORT\tPASV\tRETR");
    msg_client(server, "STOR\tDELE\tPWD\tLIST");
    msg_client(server, "HELP\tNOOP");
}
