#include <general.h>

void handler_child_mode(int signum, siginfo_t *info, void *f){
        printf("\nНомер сигнала: %d\n", info->si_signo);
        printf("Значение errno: %d\n", info->si_errno);
        printf("Код сигнала: %d\n", info->si_code);
        printf("Идентификатор процесса, пославшего сигнал: %d\n", info->si_pid);
        printf("Реальный идентификатор пользователя процесса, пославшего сигнал: %d\n", info->si_uid);
        printf("Реальный идентификатор пользователя процесса, пославшего сигнал: %d\n", info->si_uid);
        return;
}

void mode_child(){
        struct sigaction std_s;
        std_s.sa_sigaction = handler_std_mode;
        std_s.sa_flags = SA_SIGINFO;
        if(sigaction(SIGUSR1, &std_s, 0 == -1)){
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
