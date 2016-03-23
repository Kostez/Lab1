#include <general.h>

int signal_c = 0;

void handler_posix_mode(int signum, siginfo_t *info, void *f){
        fprintf(stderr, "PARENT: N=%i | MYPID=%i | PARENTPID=%i | RANDOMPOSIXSIGNALSENTNO=%i | RANDOMVALUE=%i\n", 
			signal_c, info->si_pid, getpid(), signum, info->si_value.sival_int);
        signal_c++;
}

void mode_posix(int amount) {
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = &handler_posix_mode;

	sigset_t set;
	//sigfillset(&set);
	//sigprocmask(SIG_BLOCK, &set, NULL);
	if(sigaction(SIGRTMIN, &sa, NULL) == -1){
		perror("Ошибка: не удается обработать сигнал SIGRTMIN");
	}

	int j = 0;
	for (j = 0; j < SIGRTMAX; j++) {
		sigaction(SIGRTMIN + j, &sa, NULL);
	}

	pid_t pid = fork();
	if (pid == 0) {
		// Child-процесс
		int i = 0;

		int range = 1 + SIGRTMAX - SIGRTMIN;
		int buckets = RAND_MAX / range;
		int limit = buckets * range;

		for (i = 0; i < amount; ++i) {
			union sigval value;

			int r_signal;
			do {
				r_signal = rand();
			} while (r_signal >= limit);

			r_signal = SIGRTMIN + (r_signal / buckets);

			value.sival_int = rand();





			sigqueue(getppid(), r_signal, value);
			fprintf(stderr, "CHILD: N=%i | MYPID=%i | PPID=%i | POSIXSIGNALNO=%i | VALUE=%i\n", 
				i, getpid(), getppid(), r_signal, value.sival_int);
		}
	} else if(pid > 0) {
		printf("Parent: PID=%d, GID=%d\n", getpid(), getpgid(getpid()));
		sleep(10);
		
		int status;
		if (wait(&status) > 0) {
			exit( EXIT_SUCCESS );
		} else {
			perror("Failed to handle child-zombie");
			exit( EXIT_FAILURE );
		}
	}
}
	struct sigaction posix_s;
	posix_s.sa_sigaction = handler_posix_mode;
	posix_s.sa_flags = SA_SIGINFO;
	
	int diapozon = SIGRTMAX - SIGRTMIN;
	
	int i = SIGRTMIN;
	for (; i < SIGRTMAX; i++) {
    		(sigaction(i, &posix_s, NULL) == -1);
	}
	
	pid_t pid;
	
	int j;
	switch(pid = fork()){
		case -1:;
			break;
		case 0:;
			union sigval val;
			int randomsignal=0;
			
			for(j = 0;j<amount;j++) {
				srand(time(0));
				randomsignal = SIGRTMIN+rand()%diapozon;
				val.sival_int = 1+rand()%1000;
				sigqueue(getppid(), randomsignal, val);
				fprintf(stderr, "CHILD: N=%i | MYPID=%i | PARENTPID=%i | RANDOMPOSIXSIGNALSENTNO=%i | RANDOMVALUE=%i\n", 
					j, getpid(), getppid(), randomsignal, val.sival_int);
			};
			break;
		default:;
			printf("PARENT: PID=%d, GID=%d\n", getpid(), getpgid(getpid()));
			break;
	}
}
