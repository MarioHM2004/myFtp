/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/

#include "../../include/server.h"

void stor_errors(server_t *server, char **args, int *file_fd)
{
    if (!server->is_logged)
        return msg_client(server, get_messages(NOT_LOGGED_IN));
    if (args[1] == NULL)
        return msg_client(server, get_messages(INVALID_ARGUMENTS));
    *file_fd = open(args[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (file_fd < 0) {
        perror("open");
        return msg_client(server, get_messages(INVALID_FILE));
    }
    server->accepted_data_socket = accept_data_connection(server);
    msg_client(server, "150 File status okay; about to open data connection.");
}

void stor_write(server_t *server, int *file_fd,
    char *buffer, ssize_t *bytes_read)
{
    int total_bytes_written = 0;
    ssize_t bytes_written;

    while (total_bytes_written < *bytes_read) {
        bytes_written = write(*file_fd,
            buffer + total_bytes_written, *bytes_read - total_bytes_written);
        if (bytes_written < 0) {
            perror("write");
            msg_client(server, get_messages(TRANSFER_FAILED));
            close(*file_fd);
            close(server->accepted_data_socket);
            return;
        }
        total_bytes_written += bytes_written;
    }
}

void cmd_stor(server_t *server, char **args)
{
    int file_fd;
    char *buffer = malloc(4096);
    ssize_t bytes_read;

    stor_errors(server, args, &file_fd);
    while (1) {
        bytes_read = read(server->accepted_data_socket, buffer, 4096);
        if (bytes_read == 0)
            break;
        stor_write(server, &file_fd, buffer, &bytes_read);
    }
    close(file_fd);
    close(server->accepted_data_socket);
    server->accepted_data_socket = -1;
    free(buffer);
    msg_client(server,
        "226 Closing data connection. File transfer successful.");
}
