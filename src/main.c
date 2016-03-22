#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <getopt.h>


/*
 *
 */


void worksignalss(void);

void mode_std(void);
void mode_child(void);
void mode_posix(int amount);
void mode_kill(int signo, int validkillpid);
void mode_pipe(void);

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

int main(int argc, char** argv) {

    const char* short_options = "m:a::s::p::";
    const char* modes[] = {"std", "child", "posix", "kill", "pipe"};
    const struct option long_options[] = {
        {"mode",required_argument,NULL,'m'},
        {"amount",optional_argument,NULL,'a'},
        {"signal",optional_argument,NULL,'s'},
        {"pid",optional_argument,NULL,'p'},
    };
    int rez;
    int option_index;
    int colparam = 0;
    while ((rez=getopt_long(argc,argv,short_options,
                long_options,&option_index))!=-1){
        switch(rez){
            case 'm': {
                colparam = 1;
                printf("Case m \n");
                int i = 0;
                for(; i < 5; i++) {
                    if(strcmp(optarg,modes[i]) == 0) {
                for(; i < 5; i++) {
                    if(strcmp(optarg,modes[i]) == 0) {
                        params.modes_e = i;
                        break;
                    }
                }
                if(5 == i){
                    fprintf(stderr, "Unknown mode\n");
                }
                break;
            };
            case 'a': {
                colparam = 1;
                printf("Case a \n");
                params.amount = atoi(optarg);
                break;
            };
            case 's': {
                colparam = 1;
                printf("Case s \n");
                params.signalname = atoi(optarg);
                break;
            };
            case 'p': {
                colparam = 1;
                printf("Case p \n");
                params.pid = atoi(optarg);
                break;
            };
            default:
                fprintf(stderr, "Unknown param\n");
                break;
        }
    }
    if(colparam == 0){
        printf("Use README.MD to run with parameters\n");
        return 0;
    }
    worksignalss();
    while(1) {
        sleep(1);
    }
    return EXIT_SUCCESS;
}


void handler_std_mode(int signum, siginfo_t *info, void *f){
        fprintf(stderr, "\nNumber of signal is %d\nPID of process is %d\nGID of process is %d\n\n", signum, info->si$
        return;
}


void mode_std(){
        struct sigaction std_s;
        std_s.sa_sigaction = handler_std_mode;
        std_s.sa_flags = SA_SIGINFO;
        if(sigaction(SIGUSR1, &std_s, 0 == -1)){
                perror(NULL);
        if(sigaction(SIGUSR1, &std_s, 0 == -1)){
                perror(NULL);
                exit(EXIT_FAILURE);
        }
        if(sigaction(SIGUSR2, &std_s, 0) == -1){
                perror(NULL);
                exit(EXIT_FAILURE);
        }
        if(sigaction(SIGHUP, &std_s, 0) == -1){
                perror(NULL);
                exit(EXIT_FAILURE);
        }
}

void mode_child(){

}

void mode_posix(int amount){

}

void mode_kill(int signo, int validkillpid){

}

void mode_pipe(){

}

void worksignalss(){
    switch(params.modes_e){
        case 0:
            printf("case0");
            mode_std();
            break;
        case 1:
            printf("case1");
            mode_child();
            break;
        case 2:
            printf("case2");
            if(0 < params.amount)
                mode_posix(params.amount);
            else{
                printf("Quontity of signal must be more 0 \n");
                exit(EXIT_FAILURE);
            }
            break;
        case 3:
            printf("case3");
            if(0 == params.signalname){
                fprintf(stderr, "Signal is not set\n");
                exit(EXIT_FAILURE);
            }
            if(0 == params.pid){
                fprintf(stderr, "Process ID is not set\n");
                exit(EXIT_FAILURE);
               fprintf(stderr, "Process ID is not set\n");
                exit(EXIT_FAILURE);
            }
            mode_kill(params.signalname, params.pid);
            break;
        case 4:
            printf("case4");
            mode_pipe();
            break;
    }
}
