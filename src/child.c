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
	pid_t child_pid = fork();
	
	if(0 == child_pid) {
		srand(time(0));
		randomtime = 1+rand()%5;
		printf("CHILD, Sleep for %d", randomtime);
		sleep(randomtime);
	} else if(0 < child_pid) {
		if(sigaction(SIGCHLD, &child_s, 0) == -1) {
			perror(NULL);
			exit(1);
		}
		perror(NULL);
	}
}
