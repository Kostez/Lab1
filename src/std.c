#include <general.h>

void handler_std_mode(int signum, siginfo_t *info, void *f){
        fprintf(stderr, "\nNumber of signal is %d\nPID of process is %d\nGID of process is %d\n\n", signum, info->si_pid, getpgid(info->si_pid));
        return;
}

void mode_std(){
        struct sigaction std_s;
        std_s.sa_sigaction = handler_std_mode;
        std_s.sa_flags = SA_SIGINFO;
        if(sigaction(SIGUSR1, &std_s, 0) == -1){
                perror(NULL);
                exit(1);
        }
        if(sigaction(SIGUSR2, &std_s, 0) == -1){
                perror(NULL);
                exit(1);
        }
        if(sigaction(SIGHUP, &std_s, 0) == -1){
                perror(NULL);
                exit(1);
        }
}
