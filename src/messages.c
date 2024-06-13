/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** error messages init
*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../include/server.h"

void init_messages(char *messages[])
{
    messages[ALL_GOOD] = "??? This should be an error";
    messages[INVALID_COMMAND] = "500 Syntax error, command unrecognized";
    messages[INVALID_PASSWORD] = "530 Authentication failed.";
    messages[INVALID_USERNAME] = "530 Authentication failed.";
    messages[NOT_LOGGED_IN] = "530 Please login with USER and PASS.";
    messages[INVALID_ARGUMENTS] =
        "501 Syntax error in parameters or arguments";
    messages[USER_LOGGED] =
        "421 User already logged in, closing control connection";
    messages[NEED_ACCOUNT] = "332 Need account for login.";
    messages[WRONG_PATH] = "550 Failed to change directory.";
    messages[INVALID_FILE] = "550 No such file or directory.";
}

const char *get_messages(enum ErrorKinds kind)
{
    static bool init = false;
    static char *messages[_KIND_COUNT];

    if (!init) {
        init_messages(messages);
        init = true;
    }
    if (kind == _KIND_COUNT) {
        return NULL;
    }
    return messages[kind];
}

void msg_client(server_t *server, const char *msg)
{
    int length = 0;

    if (msg == NULL)
        return msg_client(server, "XXX null message :(");
    length = strlen(msg);
    write(server->client_socket, msg, length);
    write(server->client_socket, "\r\n", 2);
}

void msg_data_socket(int accepted_data_socket, const char *msg)
{
    int length = 0;

    length = strlen(msg);
    write(accepted_data_socket, msg, length);
}

void build_response(server_t *server, char *server_ip, int *port)
{
    char response[256];
    unsigned int h1 = 0;
    unsigned int h2 = 0;
    unsigned int h3 = 0;
    unsigned int h4 = 0;
    int p2 = 0;
    int p1 = 0;

    p1 = *port / 256;
    p2 = *port % 256;
    sscanf(server_ip, "%u.%u.%u.%u", &h1, &h2, &h3, &h4);
    snprintf(response, sizeof(response),
        "227 Entering Passive Mode (%u,%u,%u,%u,%d,%d)."
            , h1, h2, h3, h4, p1, p2);
    msg_client(server, response);
}
