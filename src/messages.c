/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** error messages init
*/

#include <stdbool.h>
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
