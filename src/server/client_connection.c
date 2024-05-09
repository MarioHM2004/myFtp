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
#include "../../include/server.h"

void send_msg_to_client(server_s *server, char *msg)
{
    char *server_message = malloc(sizeof(char)*strlen(msg)+1);

    strcpy(server_message, msg);
    if (write(server->i, server_message, strlen(server_message)) == -1) {
        error("write failed");
    }
    free(server_message);
}

void client_commands(server_s *server)
{
    // write(server_socket, command_arr[0], strlen(command_arr[0]));
    // write(server_socket, command_arr[1], strlen(command_arr[1]));
    printf("-->%s\n-->%s\n", server->command_arr[0], server->command_arr[1]);
    if (strcmp(server->command_arr[0], "USER") == 0
        && strncmp(server->command_arr[1], "Anonymous", 9) == 0)
        send_msg_to_client(server, "331 User name okay, need password.\n");
    else if (strcmp(server->command_arr[0], "QUIT") == 0) {
        send_msg_to_client(server, "221\n");
    } else
        command_error(server);
}

void command_parsing(server_s *server)
{
    char *newl = strchr(server->client_response, '\n');
    char *command = strtok(server->client_response, " ");
    server->command_arr = malloc(sizeof(char *) * 3);

    if (newl)
        *newl = 0;
    memset(server->command_arr, 0, sizeof(char *) * 3);
    for (int i = 0; command != NULL; i++) {
        if (i >= 3)
            command_error(server);
        server->command_arr[i] = command;
        command = strtok(NULL, " ");
    }
    client_commands(server);
    free(server->command_arr);

}

void client_connection(server_s *server)
{
    while(1){
    server->client_response = malloc(sizeof(char)*500);
    if (read(server->i, server->client_response, 500) == -1)
        error("read failed");
    printf("client send a message\n");
    command_parsing(server);
    free(server->client_response);
    server->client_response = NULL;
    }
}
