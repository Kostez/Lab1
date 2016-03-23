#include <general.h>

pid_t child;
pid_t parent;
struct list *first;
struct list *last;

struct sigaction sa;

int signal_c = 0;

int resieved_signals_count = 0;

void mode_posix(int amount_of_signals) {
	sa.sa_sigaction = handler_posix_mode;
			int i=SIGRTMIN;
			for(; i<=SIGRTMAX; i++)
			{
				if(sigaction(i, &sa, 0)==-1)
				{
					perror(NULL);
					exit(EXIT_FAILURE);
				}
			}
			if(sigaction(SIGCHLD, &sa, 0)==-1)
			{
				perror(NULL);
				exit(EXIT_FAILURE);
			}
			int diap = SIGRTMAX - SIGRTMIN;
			parent = getpid();
			child = fork();			
			switch(child)
			{
				case -1:
				{
					perror(NULL);
					exit(EXIT_FAILURE);
					break;
				};
				case 0: //fork
				{
					child = getpid();
					union sigval qval1;
					int signo=0;
					srand(time(0));
					printf("[CHILD]\n");
					printf("|  N  | MYPID | PARENT | SIGNO | VALUE |\n");
					int i=0;
					for(;i<cmd->amount;i++)
					{
						qval1.sival_int = rand()%100;
						signo = SIGRTMIN+rand()%diap;
						sigqueue(parent,signo,qval1);
						printf("|%5d|%7d|%8d|%7d|%7d|\n",i+1,child,parent,signo,qval1.sival_int);
					}
					sleep(1);
					exit(3);
				};
				default:
				{
					break;
				};
			}
}

void handler_posix_mode(int signal, siginfo_t *siginfo, void *context) {
	if(signal==SIGCHLD)
	{
		struct list *cur = first;
		printf("[PARENT]\n");
		printf("|  N  | MYPID | CHILD | SIGNO | VALUE |\n");
		int i =1;
		while(cur!=NULL)
		{
			printf("|%5d|%7d|%7d|%7d|%7d|\n",i,parent,child,cur->siginfo.si_signo,cur->siginfo.si_value.sival_int);
			i++;
			cur = cur->next;
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		if(first==NULL)
		{
			struct list *cur = (struct list*)malloc(sizeof(struct list));
			if(cur==NULL)
			{
				perror(NULL);
				exit(EXIT_FAILURE);
			}
			memcpy(&(cur->siginfo),siginf,sizeof(siginfo_t));
			cur->next = NULL;
			first = cur;
			last = cur;
		}
		else
		{
			struct list *cur = (struct list*)malloc(sizeof(struct list));
			if(cur==NULL)
			{
				perror(NULL);
				exit(EXIT_FAILURE);
			}
			memcpy(&(cur->siginfo),siginf,sizeof(siginfo_t));
			cur->next = NULL;
			last->next=cur;
			last = cur;
		}
	}
	return;
}
