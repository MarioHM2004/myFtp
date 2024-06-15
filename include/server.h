/*
** EPITECH PROJECT, 2024
** include.h
** File description:
** header files
*/

#include <netinet/in.h>
#include <stddef.h>
#include <sys/select.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>

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
    int port;
    struct sockaddr_in client_addr;
    struct sockaddr_in server_addr;
    int server_socket;
    int client_sockets[FD_SETSIZE];
    int client_socket;
    int data_socket;
    int accepted_data_socket;
    int max_server_socket_so_far;
    char *client_response;
    fd_set current_sockets;
    fd_set ready_sockets;
    char **command_arr;
    user_t *users;
    bool is_logged;
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
    NOT_LOGGED_IN,
    INVALID_ARGUMENTS,
    USER_LOGGED,
    NEED_ACCOUNT,
    WRONG_PATH,
    INVALID_FILE,
    TRANSFER_FAILED,
    _KIND_COUNT,
};

void args_handling(server_t *server, int ac, char **av);
void error(const char *msg);
void msg_client(server_t *server, const char *msg);
void client_connection(server_t *server, int client_socket);
void run_server(server_t *server);
int create_server_socket(server_t *server);
void client_commands(server_t *server);
void command_parsing(server_t *server);
void cmd_quit(server_t *server, char **args);
void cmd_user(server_t *server, char **args);
void cmd_pass(server_t *server, char **args);
void cmd_pwd(server_t *server, char **args);
void cmd_cwd(server_t *server, char **args);
void cmd_cdup(server_t *server, char **args);
void cmd_list(server_t *server, char **args);
void cmd_noop(server_t *server, char **args);
void cmd_dele(server_t *server, char **args);
void cmd_pasv(server_t *server, char **args);
void cmd_help(server_t *server, char **args);
void cmd_retr(server_t *server, char **args);
void cmd_stor(server_t *server, char **args);
void init_users(server_t *server);
const char *get_messages(enum ErrorKinds kind);
void strip_spaces(char *data);
void trim_trailing_spaces(char *data);
int skip_spaces(char *data, int index);
bool is_end_of_string(char ch);
int count_tokens(char *data);
void init_is_logged(server_t *server);
void init_path(char **av);
char *get_path(void);
int accept_data_connection(server_t *server);
void msg_data_socket(int accepted_data_socket, const char *msg);
void build_response(server_t *server, char *server_ip, int *port);

#endif
