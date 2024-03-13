/*
** EPITECH PROJECT, 2024
** include.h
** File description:
** header files
*/

#ifndef SERVER_H
    #define SERVER_H

void usage_help(int ac, char **av);
void error(const char *msg);
void command_error(int server_socket);
void send_msg_to_client(int server_socket, char *msg);
void client_connection(int server_socket);
void run_server(int server_socket);
int create_server_socket(int port);

#endif
