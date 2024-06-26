/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/

#include "../../include/server.h"

void cmd_user(server_t *server, char **args)
{
    size_t length = 0;
    char *username = args[1];
    user_t *user = server->users;

    for (int i = 0; args[i] != NULL; i++)
        length++;
    if (length != 2 || username == NULL)
        return msg_client(server, get_messages(INVALID_ARGUMENTS));
    if (server->is_logged && (strcmp(user->username, username) == 0))
        return msg_client(server, get_messages(USER_LOGGED));
    if (username) {
        user->awaiting_pass = server->client_socket;
        user->username = username;
        return msg_client(server, "331 User name okay, need password.");
    }
}

void cmd_pass(server_t *server, char **args)
{
    char *password = args[1];
    user_t *user = server->users;
    bool is_awaiting_pass =
        (user->awaiting_pass & server->client_socket) == server->client_socket;

    if (server->is_logged || !is_awaiting_pass)
        return msg_client(server, get_messages(NEED_ACCOUNT));
    if (((strlen(user->password) == 0) && password == NULL)
        || (strcmp(user->password, password) == 0)) {
        user->logged_in = server->client_socket;
        user->awaiting_pass = 0;
        return msg_client(server, "230 User logged in, proceed.");
    }
    if (password == NULL)
        return msg_client(server, get_messages(INVALID_PASSWORD));
    if (strcmp(user->password, password) != 0)
        return msg_client(server, get_messages(INVALID_PASSWORD));
}
