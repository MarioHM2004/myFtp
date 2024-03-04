/*
** EPITECH PROJECT, 2024
** client.c
** File description:
** client socket
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(int ac, char **av)
{
    int server_sock;
    char server_response[256];

    server_sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(av[2]));
    server_addr.sin_addr.s_addr = atoi(av[1]);

    int connection_status = connect(server_sock, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (connection_status == -1) {
        perror("There was an error making a connection to the remote socket \n\n");
        exit(84);
    }

    recv(server_sock, &server_response, sizeof(server_response), 0);

    printf("Server said: %s\n", server_response);

    close(server_sock);

    return 0;
}
