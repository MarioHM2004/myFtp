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
#include "../include/include.h"

void error(const char *msg)
{
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}

void command_error(int server_response)
{
    char *msg = "xxx Error (RFC compliant)";
    char *error_message = malloc(sizeof(char)*strlen(msg)+1);
    strcpy(error_message, msg);
    if (write(server_response, &error_message, strlen(error_message)) == -1) {
        error("write failed");
    }
    free(error_message);
}

void send_msg_to_client(int server_response, char *msg)
{
    char *server_message = malloc(sizeof(char)*strlen(msg)+1);
    strcpy(server_message, msg);
    if (write(server_response, &server_message, strlen(server_message)) == -1) {
        error("write failed");
    }
    printf("%s", server_message);
    free(server_message);
}

void usage_help(int ac, char **av)
{
    if (av[1] && strcmp(av[1], "-help") == 0) {
        printf("USAGE: ./myftp <port> <path>\n\
    <port>  is the port number on which the server socket listens\n\
    <path>  is the path to the home directory for the Anonymous user\n");
        exit(EXIT_SUCCESS);
    }
    /*else if (ac != 3) {
        error("usage: ./myftp <port> <path>\n\
    for more info: ./myftp -help");
    }*/
}
