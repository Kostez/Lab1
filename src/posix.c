#include <general.h>

void mode_posix(int n_signals) {
	struct sigaction sa;
	struct sigaction saChild;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_posix_child;
	
	saChild.sa_flags = SA_SIGINFO;
	saChild.sa_sigaction = handler_posix_mode;
	
	int i=SIGRTMIN;
	for(; i<SIGRTMAX; i++) {
		if(sigaction(i, &sa, 0)==-1) {
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	
	sigset_t mask;
	sa.sa_mask = mask; 
	
	sigprocmask(SIG_BLOCK, &mask, NULL);
	
	sigaction(SIGCHLD, &saChild, 0);
	
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
		sigprocmask(SIG_UNBLOCK, &mask, NULL);
		sleep(10);
		int status = 0;
		if (wait(&status) > 0) {
			exit( EXIT_SUCCESS );
		}
}

void handler_posix_mode(int signal, siginfo_t *siginfo, void *context) {
	sigprocmask(SIG_BLOCK, &mask, NULL);
	fprintf(stderr,"PARENT\t %i | %i | %i | %i | %i\n", signal_c, getpid(), getppid(), signal, siginfo->si_value.sival_int);
	signal_c++;
	sigprocmask(SIG_UNBLOCK, &mask, NULL);
}
