/*
** EPITECH PROJECT, 2024
** include.h
** File description:
** header files
*/
 
#include <netinet/in.h>
#include <stddef.h>
#include <sys/select.h>
 
#ifndef SERVER_H
    #define SERVER_H
    #define MAX_BYTES 1024
 
typedef struct {
    char *username;
    char *password;
    int logged_in;
    int awaiting_pass;
} user_t;
 
typedef struct server {
    char *path;
    struct sockaddr_in client_addr;
    int server_socket;
    int client_sockets[FD_SETSIZE];
    int client_socket;
    int max_server_socket_so_far;
    char *client_response;
    fd_set current_sockets;
    fd_set ready_sockets;
    char **command_arr;
    user_t *users;
} server_t;
 
typedef void (*cmd_fn_t)(server_t *, char **args);
 
typedef struct {
    const char *cmd;
    cmd_fn_t fn;
} cmd_t;
 
enum ErrorKinds {
    ALL_GOOD,
    INVALID_COMMAND,
    INVALID_PASSWORD,
    INVALID_USERNAME,
    INVALID_ARGUMENTS,
    USER_LOGGED,
    NEED_ACCOUNT,
    _KIND_COUNT,
};
 
void args_handling(server_t *server, int ac, char **av);
void error(const char *msg);
void send_msg_to_client(server_t *server, const char *msg);
void client_connection(server_t *server, int client_socket);
void run_server(server_t *server);
int create_server_socket(server_t *server, int port);
void client_commands(server_t *server);
void command_parsing(server_t *server);
void cmd_quit(server_t *server, char **args);
void cmd_user(server_t *server, char **args);
void cmd_pass(server_t *server, char **args);
void cmd_pwd(server_t *server, char **args);
void init_users(server_t *server);
const char *message(enum ErrorKinds kind);
 
#endif
