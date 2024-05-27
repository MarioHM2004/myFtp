/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** initialise
*/

#include <stdlib.h>
#include <unistd.h>
#include "../include/server.h"

void init_path(server_t *server)
{
    if (chdir(server->path) != 0) {
        error("chdir() error");
    }
}

void init_users(server_t *server)
{
    user_t *user = NULL;

    (*server).users = malloc(sizeof(*server->users));
    user = server->users + 0;
    user->username = "Anonymous";
    user->password = "";
    user->logged_in = 0;
    user->awaiting_pass = 0;
}

void init_is_logged(server_t *server)
{
    user_t *user = server->users;

    server->is_logged =
        (user->logged_in & server->client_socket) == server->client_socket;
}
