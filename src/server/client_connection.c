/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server socket
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../../include/include.h"

void send_msg_to_client(int server_socket, char *msg)
{
    char *server_message = malloc(sizeof(char)*strlen(msg)+1);

    strcpy(server_message, msg);
    if (write(server_socket, server_message, strlen(server_message)) == -1) {
        error("write failed");
    }
    free(server_message);
}

void client_commands(int server_socket, char *client_response, char** command_arr)
{
    write(server_socket, command_arr[0], strlen(command_arr[0]));
    write(server_socket, command_arr[1], strlen(command_arr[1]));
    if (strcmp(command_arr[0], "USER") == 0
        && strcmp(command_arr[1], "Anonymous") == 0)
        send_msg_to_client(server_socket, "User name okay, need password.\n");
    else
        command_error(server_socket);
}

void command_parsing(int server_socket, char *client_response)
{
    char *command = strtok(client_response, " ");
    char **command_arr = malloc(sizeof(char *) * 2);
    char *newl = NULL;

    for (int i = 0; command != NULL; i++) {
        if (i >= 3)
            command_error(server_socket);
        command_arr[i] = command;
        command = strtok(NULL, " ");
        if (command == NULL)
            continue;
        newl = strrchr(command, '\n');
        if (!newl)
            continue;
        *newl = '\0';
    }
    client_commands(server_socket, client_response, command_arr);
}

void client_connection(int server_socket)
{
    char *client_response = malloc(sizeof(char)*500);

    if (read(server_socket, client_response, 500) == -1)
        error("read failed");
    command_parsing(server_socket, client_response);
    close(server_socket);
    free(client_response);
}

