#include <general.h>

void mode_kill(int signo, int validkillpid){		
 		
}		
 		
void mode_pipe(){		
 		
}
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
                        params.modes_e = i;
                        break;
                    }
                }
                if(5 == i){
                    fprintf(stderr, "Unknown mode\n");
                    return 0;
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
                exit(0);
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
    return 0;
}

void worksignalss(){
    switch(params.modes_e){
        case 0:
            printf("case0\n");
            mode_std();
            break;
        case 1:
            printf("case1\n");
            mode_child();
            break;
        case 2:
            printf("case2\n");
            if(0 < params.amount)
                mode_posix(params.amount);
            else{
                printf("Quontity of signal must be more 0\n");
                exit(1);
            }
            break;
        case 3:
            printf("case3");
            if(0 == params.signalname){
                fprintf(stderr, "Signal is not set\n");
                exit(1);
            }
            if(0 == params.pid){
                fprintf(stderr, "Process ID is not set\n");
                exit(1);
            }
            mode_kill(params.signalname, params.pid);
            break;
        case 4:
            printf("case4\n");
            mode_pipe();
            break;
    }
}
