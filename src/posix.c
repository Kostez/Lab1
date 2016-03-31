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
	
	int status;
	pid_t pid = fork();
	if (pid == 0) {
			srand(time(0));
			int i=0;
			for(; i < n_signals; i++) {
				union sigval svalue;
				int random_signal;
				svalue.sival_int = rand();
				random_signal = SIGRTMIN+rand()%(SIGRTMAX);
				sigqueue(getppid(),random_signal,svalue);
				printf("CHILD:\t%i | %i | %i | %i | %i\n", i, getpid(), getppid(), random_signal, svalue.sival_int);
			}
	}  else if(pid > 0) {
			printf("Parent: PID=%d, GID=%d\n", getpid(), getpgid(getpid()));
			if (wait(&status) > 0) {
				exit( EXIT_SUCCESS );
			} else {
			perror("Failed to handle child-zombie");
			exit( EXIT_FAILURE );
		}
	}
}

void handler_posix_mode(int signal, siginfo_t *siginfo, void *context) {
	printf("PARENT:\t %i | %i | %i | %i | %i\n", signal_c, siginfo->si_pid, getpid(), signal, siginfo->si_value.sival_int);
	signal_c++;
}
