#include <general.h>

int signal_c = 0;
int diapozon = SIGRTMAX-SIGRTMIN;
void mode_posix(int n_signals) {
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_posix_mode;
	printf("%i\n", SIGRTMIN);
	printf("%i\n", SIGRTMAX);
	int i=SIGRTMIN;
	for(; i<SIGRTMAX; i++) {
		if(sigaction(i, &sa, 0)==-1) {
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	
	int status;
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
			sleep(10);
			status = 0;
//			int status;
			if (wait(&status) > 0) {
				exit( EXIT_SUCCESS );
			} 
			break;
		};
	}
}

void handler_posix_mode(int signal, siginfo_t *siginfo, void *context) {
	fprintf(stderr,"PARENT\t %i | %i | %i | %i | %i\n", signal_c, getpid(), getppid(), signal, siginfo->si_value.sival_int);
	signal_c++;
}
