#include <general.h>

sigset_t mask;
int signal_c=0;
char str[30][40];
void mode_posix(int n_signals) {
	
	int i = 0;
	/*
	for(; i< 30*40; i++){
		str[0][i] = ' ';
	}
	
	for(; i< 30; i++){
		str[0][i*40] = '\0';
	}
*/	
	struct sigaction sa;
	struct sigaction saChild;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_posix_mode;
	
	saChild.sa_flags = SA_SIGINFO;
	saChild.sa_sigaction = handler_posix_child;
	
	i=SIGRTMIN;
	for(; i<SIGRTMAX; i++) {
		if(sigaction(i, &sa, 0)==-1) {
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	
	saChild.sa_mask = mask;
	
	sigaction(SIGCHLD, &saChild, 0);
	
	sigprocmask(SIG_BLOCK, &mask, NULL);
	
	int diapozon = SIGRTMAX-SIGRTMIN;
	
	pid_t pid = fork();
	switch(pid) {
		case -1:
		{
			perror("fork err");
			exit(1);
		};
		case 0:
		{
			srand(time(0));
			int k=0;
			for(; k < n_signals; k++) {
				union sigval svalue;
				int random_signal;
				svalue.sival_int = rand()%100;
				random_signal = SIGRTMIN+rand()%diapozon;
				sigqueue(getppid(),random_signal,svalue);
				printf("%d\n", random_signal);
				fprintf(stderr,"CHILD: \t %i | %i | %i | %i | %i\n", k, getpid(), getppid(), random_signal, svalue.sival_int);
			}
			break;
		};
		default:
		{
			while(1){
				sleep(10);
			}
			break;
		};
	}
}

void handler_posix_child(int signal, siginfo_t *siginfo, void *context){
		
//		sleep(10);
		printf("%d\n", signal_c);
		int i=0;
		for(;i<signal_c;i++){
			printf("%s\n", str[i]);
		}
		
		int status = 0;
		if (wait(&status) > 0) {
			exit( EXIT_SUCCESS );
		}
}

void handler_posix_mode(int signal, siginfo_t *siginfo, void *context) {
	
	int i = signal_c++;
	
	sigprocmask(SIG_BLOCK, &mask, NULL);
	
	
/*	
	itoa(signal_c, &str[i][0], 10);
	itoa(getpid(), &str[i][6], 10);
	itoa(getppid(), &str[i][12], 10);
	itoa(signal, &str[i][18], 10);
	itoa(siginfo->si_value.sival_int, &str[i][24], 10);
	
	sigprocmask(SIG_UNBLOCK, &mask, NULL);*/
	sprintf(str[i], "PARENT\t %i | %i | %i | %i | %i\n", signal_c, getpid(), getppid(), signal, siginfo->si_value.sival_int);
//	signal_c++;

}
