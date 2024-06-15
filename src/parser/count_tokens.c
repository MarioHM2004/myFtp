/*
** EPITECH PROJECT, 2024
** server.c
** File description:
** server socket
*/

#include "../../include/server.h"

void count_tokens_handler(char *data, int *i,
    int *max_alloc, bool *end_of_string)
{
    if (data[*i] == ' ') {
        *i = skip_spaces(data, *i);
        if (is_end_of_string(data[*i])) {
            *end_of_string = true;
        } else {
            (*max_alloc)++;
        }
    } else {
        if (is_end_of_string(data[*i])) {
            *end_of_string = true;
        } else {
            (*i)++;
        }
    }
}

int count_tokens(char *data)
{
    int max_alloc = 1;
    int i = 0;
    bool end_of_string = false;

    while (!end_of_string) {
        count_tokens_handler(data, &i,
            &max_alloc, &end_of_string);
    }
    return max_alloc;
}
