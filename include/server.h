/*
** EPITECH PROJECT, 2024
** include.h
** File description:
** header files
*/

#ifndef SERVER_H
    #define SERVER_H

#include <sys/select.h>
#define MAX_BYTES 1024

typedef struct server_s {
    int server_socket;
    int client_socket;
    char *client_response;
    fd_set current_sockets;
    fd_set ready_sockets;
    char **command_arr;
    int i;
} server_s;

typedef void (*cmd_fn_t)(server_s *, char **args);

typedef struct {
    const char *cmd;
    cmd_fn_t fn;
} cmd_t;

void usage_help(int ac, char **av);
void error(const char *msg);
void command_error(server_s *server, char *msg);
void send_msg_to_client(server_s *server, char *msg);
void client_connection(server_s *server);
void run_server(server_s *server);
int create_server_socket(server_s *server, int port);
void client_commands(server_s *server);
void command_parsing(server_s *server);
void cmd_quit(server_s *server, char **args);
void cmd_user(server_s *server, char **args);

#endif
