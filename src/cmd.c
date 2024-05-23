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
#include "../include/server.h"

void cmd_user(server_t *server, char **args)
{
    enum ErrorKinds error = ALL_GOOD;
    size_t length = 0;
    char *username = args[1];

    for (int i = 0; args[i] != NULL; i++)
        length++;
    user_t *user = server->users;
    bool is_logged = (user->logged_in & server->client_socket) == server->client_socket;
    if (length != 2 || username == NULL)
        return send_msg_to_client(server, message(INVALID_ARGUMENTS));
    if (is_logged && (strcmp(user->username, username) == 0))
        return send_msg_to_client(server, message(USER_LOGGED));
    if (strcmp(user->username, username) != 0)
        return send_msg_to_client(server, message(INVALID_USERNAME));
    if (strcmp(user->username, username) == 0) {
        user->awaiting_pass = server->client_socket;
        return send_msg_to_client(server, "331 User name okay, need password.");
    }
    return send_msg_to_client(server, message(error));
}

void cmd_pass(server_t *server, char **args)
{
    enum ErrorKinds error = ALL_GOOD;
    char *password = args[1];

    user_t *user = server->users;
    bool is_logged = (user->logged_in & server->client_socket) == server->client_socket;
    bool is_awaiting_pass = (user->awaiting_pass & server->client_socket) == server->client_socket;
    if (is_logged || !is_awaiting_pass)
        return send_msg_to_client(server, message(NEED_ACCOUNT));
    if (((strlen(user->password) == 0) && password == NULL) || (strcmp(user->password, password) == 0)) {
        user->logged_in = server->client_socket;
        user->awaiting_pass = 0;
        return send_msg_to_client(server, "230 User logged in, proceed.");
    }
    if (password == NULL)
        return send_msg_to_client(server, message(INVALID_PASSWORD));
    if (strcmp(user->password, password) != 0)
        return send_msg_to_client(server, message(INVALID_PASSWORD));
    return send_msg_to_client(server, message(error));
}

void cmd_quit(server_t *server, char **args)
{
    return send_msg_to_client(server, "221 Service closing control connection.");
}

void cmd_pwd(server_t *server, char **args)
{
}
