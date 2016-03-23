#include <general.h>

int signal_c = 0;

void handler_posix_mode(int signum, siginfo_t *info, void *f){
        fprintf(stderr, "PARENT: N=%i | MYPID=%i | PARENTPID=%i | RANDOMPOSIXSIGNALSENTNO=%i | RANDOMVALUE=%i\n", 
			signal_c, info->si_pid, getpid(), signum, info->si_value.sival_int);
        signal_c++;
}

void mode_posix(int amount){
	struct sigaction posix_s;
	posix_s.sa_sigaction = handler_posix_mode;
	posix_s.sa_flags = SA_SIGINFO;
	
	int i = SIGRTMIN;
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
			int j = 0;
			for(;j<amount;j++) {
				union sigval value;
				int randomsignal = 0;
				int randomvalue = 0;
			
				srand(time(0));
				randomsignal = SIGRTMIN+rand()%SIGRTMAX;
				randomvalue = 50+rand()%100;
			
				sigqueue(getppid(), randomsignal, value);
				fprintf(stderr, "CHILD: N=%i | MYPID=%i | PPID=%i | RANDOMPOSIXSIGNALSENTNO=%i | RANDOMVALUE=%i\n", 
					i, getpid(), getppid(), randomsignal, value.sival_int);
			};
			break;
		default:
			printf("PARENT: PID=%d, GID=%d\n", getpid(), getpgid(getpid()));
			break;
	}
}
