/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/

#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include "../../include/server.h"

void retr_errors(server_t *server, char **args, int *file_fd)
{
    size_t length = 0;

    for (int i = 0; args[i] != NULL; i++)
        length++;
    if (!server->is_logged)
        return msg_client(server, get_messages(NOT_LOGGED_IN));
    if (length != 2)
        return msg_client(server, get_messages(INVALID_ARGUMENTS));
    *file_fd = open(args[1], O_RDONLY);
    if (file_fd < 0)
        return msg_client(server, get_messages(INVALID_FILE));
    server->accepted_data_socket = accept_data_connection(server);
    msg_client(server, "150 File status okay; about to open data connection.");
}

void cmd_retr(server_t *server, char **args)
{
    int file_fd;
    char *buffer = malloc(4096);
    ssize_t bytes_read;

    retr_errors(server, args, &file_fd);
    while (1) {
        bytes_read = read(file_fd, buffer, 4096);
        if (bytes_read == 0)
            break;
        write(server->accepted_data_socket, buffer, bytes_read);
    }
    close(file_fd);
    close(server->accepted_data_socket);
    free(buffer);
    server->accepted_data_socket = -1;
    msg_client(server, "226 Closing data connection.");
}
