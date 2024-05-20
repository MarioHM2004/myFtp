/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** initialise
*/

#include <stdlib.h>
#include "../include/server.h"

void init_users(server_t *server)
{
    (*server).users = malloc(sizeof(*server->users));

    user_t *user = server->users + 0;
    user->username = "Anonymous";
    user->password = "";
    user->logged_in = 0;
    user->awaiting_pass = 0;
}
