#include <general.h>

void handler_child_mode(int signum, siginfo_t *info, void *f){
        printf("\nНомер сигнала: %d\n", info->si_signo);
        printf("Значение errno: %d\n", info->si_errno);
        printf("Код сигнала: %d\n", info->si_code);
        printf("Идентификатор процесса, пославшего сигнал: %d\n", info->si_pid);
        printf("Реальный идентификатор пользователя процесса, пославшего сигнал: %d\n", info->si_uid);
        printf("Выходное значение или номер сигнала: %d\n", info->si_status);
        printf("Занятое пользователем время: %li\n", info->si_utime);
        printf("Использованное системное время: %li\n", info->si_stime);
        printf("Значение сигнала: %d\n", info->si_value);
        printf("Сигнал  POSIX.1b: %d\n", info->si_int);
        printf("Сигнал  POSIX.1b: %d\n", info->si_ptr);
        printf("Адрес в памяти, приводящий к ошибке: %d\n", info->si_addr);
        printf("Общее событие: %d\n", info->si_band);
        printf("Описатель файла: %d\n\n", info->si_fd);
        exit(0);
}

void mode_child(){
        struct sigaction child_s;
        int randomtime = 0;
        child_s.sa_sigaction = handler_child_mode;
        child_s.sa_flags = SA_SIGINFO;
	pid_t child_pid;
	
	switch(child_pid = fork()) {
  		case -1:
        	 	perror("fork"); /* произошла ошибка */
        	 	exit(1); /*выход из родительского процесса*/
  		case 0:
        		printf(" CHILD: Это процесс-потомок!\n");
          		printf(" CHILD: Мой PID -- %d\n", getpid());
          		printf(" CHILD: PID моего родителя -- %d\n", getppid());
          		srand(time(0));
			randomtime = 1+rand()%5;
			printf("CHILD, Sleep for %d", randomtime);
			sleep(randomtime);	
          		printf(" CHILD: Выход!\n");
  		default:
          		printf("PARENT: Это процесс-родитель!\n");
        		printf("PARENT: Мой PID -- %d\n", getpid());
          		printf("PARENT: PID моего потомка %d\n",pid);
          		sigaction(SIGCHLD, &child_s, 0);
          		printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
        		wait();
          		printf("PARENT: Выход!\n");
  	}
}
