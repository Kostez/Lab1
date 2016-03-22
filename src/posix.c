#include <general.h>

int signal_c = 0;

void handler_posix_mode(int signum, siginfo_t *info, void *f){
        
        fprintf(stderr, " %i | %i | %i | %i | %i\n", signal_c, info->si_pid, getpgid(), signal, );
        signal_c++;
        return;
}

void mode_posix(int amount){
        struct sigaction posix_s;
        posix_s.sa_sigaction = handler_posix_mode;
        posix_s.sa_flags = SA_SIGINFO;
        
        
}
