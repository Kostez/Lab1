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
	
	int i = SIGRTMIN
	for (; i < SIGRTMAX; i++) {
    	if(sigaction(i, &posix_s, NULL) == -1) {
    		perror(NULL);
			exit(0);
    	}
	}
	
	pid_t pid;
	
	switch(pid = fork()){
		case -1:
			break;
		case 0:
			break;
		default:
			break;
	}
	if (pid == 0) {
		int j = 0;
		for(;j<amount;j++) {
			union sigval value;
			int randomsignal = 0;
			int randomvalue = 0;
			
			srand(time(0));
			randomsignal = SIGRTMIN+rand()%SIGRTMAX;
			randomvalue = 50+rand()%100;
			
			sigqueue(getppid(), randomsignal, value);
		};	
			
	}
}
