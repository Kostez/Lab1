#include <general.h>


int signal_c=0;
char str[30][40];
int global_n_signals;
int isexit = 0;
int signal_end = 0;


void mode_posix(int n_signals) {
	global_n_signals = n_signals;
	int i = 0;
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_posix_mode;
	
	i=SIGRTMIN;
	for(; i<SIGRTMAX; i++) {
		if(sigaction(i, &sa, 0)==-1) {
			perror(NULL);
			exit(EXIT_FAILURE);
		}
	}
	
	sigaction(SIGCHLD, &sa, 0);
	
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
		if(signal_end< global_n_signals){
			sleep(1);
		}
		printf("%d\n", signal_end);
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
	
	if(signal == SIGCHLD){
		isexit = 1;
		if(signal_end>=global_n_signals){
			handler_posix_child(signal, siginfo, context);
		}
		return;
	}
	
	int i = signal_c++;
	
	sigprocmask(SIG_BLOCK, &mask, NULL);

	sprintf(str[i], "PARENT\t %i | %i | %i | %i | %i", i, getpid(), getppid(), signal, siginfo->si_value.sival_int);
//	signal_c++;

	signal_end++;

	if((signal_end>=global_n_signals)&&(isexit > 0)){
		handler_posix_child(signal, siginfo, context);
		
	}
}
