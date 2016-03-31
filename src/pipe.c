#include <general.h>

void handle_pipe_mode(int signum, siginfo_t *siginfo, void *context) {
	const char *signal_name;

	switch(signum){
		case SIGPIPE:
			printf("SIGPIPE is  %i\n", signum);
			break;
		default:
			fprintf( stderr, "Unknown signal: %d\n", signal);
			return;	
	}
}

void mode_pipe(){
	int fd[2];
	int buf;
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_pipe_mode;
	pid_t pid;
	char *mystring = "Hello world";
	
	if (pipe(fd)<0) {
		fprintf(stderr, "pipe err" );
		exit(1);
	}

	if(sigaction(SIGPIPE, &sa, 0) == -1){
		perror("sigaction err");
		exit(1);
	}
	
	pid=fork();
	switch(pid){
		case -1:{
			perror("case -1 err\n");
			exit(1);
			break;
		};
		case 0: {
			close(fd[1]);
			close(fd[0]);
			sleep(4);
			exit(0);
		};
		default: {
			if(close(fd[0])==-1) {
				perror("close fd[0] err\n");
				exit(EXIT_FAILURE);
			}
			while(1) {
				if(write(fd[1],mystring,256)==-1) {
					perror("write err\n");
					exit(1);
				}
				sleep(1);
			}
			break;
		};
	}
}
