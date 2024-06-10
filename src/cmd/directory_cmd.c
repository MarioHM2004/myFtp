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
#include <dirent.h>
#include "../../include/server.h"

void cmd_pwd(server_t *server, char **args)
{
    char *code = "257 ";
    char *msg = " created.";
    char *cwd = malloc(1024);
    char *buff = malloc(1024);
    int length;

    memset(buff, 0, 1024);
    if (getcwd(cwd, 1024) != NULL && server->is_logged) {
        length = strlen(code) + strlen(cwd) + strlen(msg);
        snprintf(buff, 1024, "%s%s%s", code, cwd, msg);
        write(server->client_socket, buff, length);
        write(server->client_socket, "\r\n", 2);
    } else {
        msg_client(server, get_messages(NOT_LOGGED_IN));
    }
    free(cwd);
    free(buff);
}

void cmd_cwd(server_t *server, char **args)
{
    size_t length = 0;

    for (int i = 0; args[i] != NULL; i++)
        length++;
    if (length > 2)
        return msg_client(server, get_messages(INVALID_ARGUMENTS));
    if (!server->is_logged)
        return msg_client(server, get_messages(NOT_LOGGED_IN));
    if (chdir(args[1]) != 0)
        return msg_client(server, get_messages(WRONG_PATH));
    msg_client(server, "250 Requested file action okay, completed.");
    server->path = get_path();
}

void cmd_cdup(server_t *server, char **args)
{
    if (!server->is_logged)
        return msg_client(server, get_messages(NOT_LOGGED_IN));
    if (chdir("../") != 0)
        return msg_client(server, get_messages(WRONG_PATH));
    msg_client(server, "200 Command okay.");
    server->path = get_path();
}

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
