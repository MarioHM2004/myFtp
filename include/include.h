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
void command_error(int server_response);
void send_msg_to_client(int server_response, char *msg);

#endif