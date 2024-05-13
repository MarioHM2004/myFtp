/*
** EPITECH PROJECT, 2024
** help.c
** File description:
** help socket
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/server.h"

void error(const char *msg)
{
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}

void usage_help(int ac, char **av)
{
    if (av[1] && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myftp <port> <path>\n\
    <port>  is the port number on which the server socket listens\n\
    <path>  is the path to the home directory for the Anonymous user\n");
        exit(EXIT_SUCCESS);
    }
    else if (ac != 3) {
        error("usage: ./myftp <port> <path>\n\
    for more info: ./myftp -help");
    }
}
