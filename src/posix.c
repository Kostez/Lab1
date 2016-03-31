#include <general.h>

int signal_c = 0;

void mode_posix(int n_signals) {
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_posix_mode;
	
	int i=SIGRTMIN;
	for(; i<=SIGRTMAX; i++) {
		if(sigaction(i, &sa, 0)==-1) {
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	
	pid_t child;
	int status;
	switch(child = fork()) {
		case -1:
			perror("fork"); /* произошла ошибка */
			exit(1); /*выход из родительского процесса*/
		case 0:
			srand(time(0));
			int i=0;
			for(; i < n_signals; i++) {
				union sigval svalue;
				int random_signal;
				svalue.sival_int = rand()%100;
				random_signal = SIGRTMIN+rand()%(SIGRTMAX-1);
				sigqueue(getppid(),random_signal,svalue);
				printf("CHILD:\t%i | %i | %i | %i | %i\n", i, getpid(), getppid(), random_signal, svalue.sival_int);
			}
		default:
			
			if (wait(&status) > 0) {
				exit( EXIT_SUCCESS );
			}
	}
}

void handler_posix_mode(int signal, siginfo_t *siginfo, void *context) {
	printf("PARENT:\t %i | %i | %i | %i | %i\n", signal_c, siginfo->si_pid, getpid(), signal, siginfo->si_value.sival_int);
	signal_c++;
}
