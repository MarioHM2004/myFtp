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

void client_commands(int server_socket,
    char *client_response, char **command_arr)
{
    if (strcmp(command_arr[0], "USER") == 0
        && strncmp(command_arr[1], "Anonymous", 9) == 0)
        send_msg_to_client(server_socket, "User name okay, need password.\n");
    else if (strcmp(command_arr[0], "QUIT") == 0 && !command_arr[1]) {
        close(server_socket);
        free(client_response);
    } else
        command_error(server_socket);
}

void command_parsing(int server_socket, char *client_response)
{
    char *newl = strchr(client_response, '\n');
    char *command = strtok(client_response, " ");
    char **command_arr = malloc(sizeof(char *) * 3);

    if (newl)
        *newl = 0;
    memset(command_arr, 0, sizeof(char *) * 3);
    for (int i = 0; command != NULL; i++) {
        if (i >= 3)
            command_error(server_socket);
        command_arr[i] = command;
        command = strtok(NULL, " ");
    }
    client_commands(server_socket, client_response, command_arr);
    free(command_arr);
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
