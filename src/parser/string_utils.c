/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server socket
*/

#include <string.h>
#include <stdbool.h>
#include "../../include/server.h"

void strip_spaces(char *data)
{
    while (*data == ' ') {
        data++;
    }
}

void trim_trailing_spaces(char *data)
{
    char *end = data + strlen(data) - 1;

    while (*end == ' ') {
        *end = '\0';
        end--;
    }
}

int skip_spaces(char *data, int index)
{
    while (data[index] == ' ') {
        index++;
    }
    return index;
}

bool is_end_of_string(char ch)
{
    return ch == '\0';
}
