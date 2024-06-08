/*
** EPITECH PROJECT, 2024
** myFtp
** File description:
** commands functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <dirent.h>
#include "../../include/server.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void cmd_pasv(server_t *server, char **args) {
    char *response = malloc(256);
    char *ip_address = strdup(inet_ntoa(server->server_addr.sin_addr));

    // Generar un puerto de datos pasivo válido
    server->passive_port = server->port + 1;

    if (!server->is_logged) {
        free(ip_address);
        free(response);
        return; // Si el usuario no está autenticado, no se procede con el comando PASV
    }

    // Crear un nuevo socket para la conexión de datos pasiva
    int data_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (data_socket == -1) {
        perror("Error al crear el socket");
        free(ip_address);
        free(response);
        return;
    }

    // Configurar la estructura de dirección del servidor para el nuevo socket
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(server->passive_port);
    printf("%d\n", server->passive_port);

    // Conectar al servidor
    int connect_status = connect(data_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (connect_status == -1) {
        perror("Error al conectar al servidor");
        free(ip_address);
        free(response);
        close(data_socket);
        return;
    }

    // Formatear la respuesta para el cliente
    int p1 = server->passive_port / 256;
    int p2 = server->passive_port % 256;
    snprintf(response, 256, "227 Entering Passive Mode (%s,%d,%d).", ip_address, p1, p2);

    // Enviar la respuesta al cliente
    msg_client(server, response);

    // Liberar memoria y cerrar el socket
    free(ip_address);
    free(response);
    close(data_socket);
}
