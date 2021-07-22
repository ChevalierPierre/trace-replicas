/*
** EPITECH PROJECT, 2017
** strace.h
** File description:
** <..>
*/
#ifndef STRACE_H_

#define STRACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <syscall.h>
#include <sys/ptrace.h>

typedef struct  s_syscalls
{
    unsigned      num;
    char          *name;
    char          man_found;
    unsigned      nparams;
    int           type_return;
    int           param1;
    int           param2;
    int           param3;
    int           param4;
    int           param5;
    int           param6;
}               t_syscalls;

enum OUTPUT_TYPE {
    NORMAL = 0,
    STRACE = 1
};

struct arguments
{
	int	o_type;	// output_type
	int	pid;
	char	**argms;
};

void init_strace(struct arguments *arg);
int looping(struct arguments *arg, pid_t pid);
void display(struct arguments *arg, long syscall, struct user_regs_struct *regs,
        pid_t pid);

#endif
