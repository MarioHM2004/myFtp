/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server socket
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int ac, char **av)
{
    if (ac < 2) {
    fprintf(stderr, "Usage: %s <port>\n", av[0]);
    return 1;
    }

    char server_message[256] = "Hello World!!!\n";

    int server_socket, client_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(av[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (server_socket == -1) {
        perror("Socket creation failed");
        return 1;
    }


    if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        return 1;
    }

    listen(server_socket, 5);

    while (1) {
        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1) {
            perror("Accept failed");
            return 1;
        }

        pid_t p = fork();
        if (p < 0) {
            perror("fork fail");
            exit(1);
        } else if (p == 0) {
            close(server_socket);
            sleep(5);
            struct sockaddr_in client_addr;
            socklen_t client_addr_len = sizeof(client_addr);
            if (getpeername(client_socket, (struct sockaddr*)&client_addr, &client_addr_len) == -1) {
                perror("getpeername failed");
                return 1;
            }
            printf("Connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            send(client_socket, server_message, sizeof(server_message), 0);
            close(client_socket);
            exit(0); 
        } else {
            close(client_socket);             
        }
    }

    return 0;
}
