/*
** EPITECH PROJECT, 2018
** main.c
** File description:
** <..>
*/

#include <getopt.h>

#include "strace.h"

static void usage(void)
{
    printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");
    exit (0);
}

static void arg_val(char **arg, int argc, int *i, struct arguments *args)
{
    int j = 0;

    if (arg[*i][0] == '-') {
        if (!strcmp(arg[*i], "--help")) {
            usage();
        } else if (!strcmp(arg[*i], "-s")) {
            args->o_type = STRACE;
            return;
        } else if (!strcmp(arg[*i], "-p")) {
            if (argc == 2)
                exit(84);
            *i = *i + 1;
            args->pid = atoi(arg[*i]);
        }
    }
    if (args->pid == 0) {
        args->argms = malloc(sizeof(char *) * ((argc - *i) + 1));
        if (args->argms == NULL)
            exit(84);
        for (j = *i; j < argc; j++) {
            args->argms[j - *i] = malloc(sizeof(char) * strlen(arg[j]) + 1);
            if (args->argms[j - *i] == NULL)
                exit (84);
            strcpy(args->argms[j - *i], arg[j]);
        }
        args->argms[j - *i] = NULL;
        *i = j;
    }
}

int main(int argc, char **argv)
{
    struct arguments    *args = malloc(sizeof(struct arguments));

    if (argc < 2) {
        printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");
        return (84);
    }
    memset(args, 0, sizeof(struct arguments));
    for (int i = 1; i < argc; i++)
        arg_val(argv, argc, &i, args);
    init_strace(args);
    for (int i = 0; args->argms[i]; i++) {
        if (args->argms[i] != NULL)
            free(args->argms[i]);
    }
    if (args->argms != NULL)
        free(args->argms);
    if (args != NULL)
        free(args);
    return (0);
}
