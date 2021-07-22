/*
** EPITECH PROJECT, 2018
** strace.c
** File description:
** <..>
*/

#include "strace.h"
#include "syscalls.h"

void init_strace(struct arguments *arg)
{
    pid_t pid = 0;

    if (arg->pid == 0) {
        pid = fork();
        switch (pid) {
            case -1:
                exit(84);
            case 0:
                ptrace(PTRACE_TRACEME, 0, 0, 0);
                execvp(arg->argms[0], arg->argms);
                exit(0);
        }
        looping(arg, pid);
    } else {
        if (ptrace(PTRACE_ATTACH, arg->pid, 0, 0))
            exit(84);
        looping(arg, (pid_t)arg->pid);
    }
}

int looping(struct arguments *arg, pid_t pid)
{
    struct user_regs_struct regs;
    int status;
    long syscall;

    while (waitpid(pid, &status, 0) && ! WIFEXITED(status)) {
        if (arg->pid == 0) {
            ptrace(PTRACE_GETREGS, pid, 0, &regs);
            ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
            ptrace(PTRACE_PEEKUSER, pid, NULL, NULL);
        } else {
            ptrace(PTRACE_GETREGS, pid, 0, &regs);
            ptrace(PTRACE_SINGLESTEP, pid, 0, 0);
        }
        syscall = (long)regs.orig_rax;
        if (syscall < 315)
            display(arg, syscall, &regs, pid);
    }
    printf("+++ exited with %d +++\n", WEXITSTATUS(status));
    if (arg->pid != 0)
        ptrace(PTRACE_DETACH, pid, 0, 0);
    return (0);
}
