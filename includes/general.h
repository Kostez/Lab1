#ifndef __LAB1__
#define __LAB1__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <getopt.h>

#define HELLOMSG "Say Hi!\r\n"

enum Modes {
        modes_std = 0,
        modes_child,
        modes_posix,
        modes_kill,
        modes_pipe
}modes_e;

struct Params {
        enum Modes modes_e;
        int amount;
        int signalname;
        int pid;
}params;

struct list {
	siginfo_t siginfo;
	struct list *next;
};

void worksignalss(void);

void mode_std(void);
void mode_child(void);
void mode_posix(int amount);
void mode_kill(int signo, int validkillpid);
void mode_pipe(void);

void handler_std_mode(int signum, siginfo_t *info, void *f);
void handler_child_mode(int signum, siginfo_t *info, void *f);
void handler_posix_mode(int signum, siginfo_t *info, void *f);
void handler_kill_mode(int signum, siginfo_t *info, void *f);
void handler_pipe_mode(int signum, siginfo_t *info, void *f);

#endif
