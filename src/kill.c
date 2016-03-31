#include <general.h>

void mode_kill(int signo, int validkillpid){
 		
 		if(validkillpid==0){
 			printf("Сигнал посылается всем процессам в группе: %d\n", validkillpid);
 		} else if(validkillpid==-1){
 			printf("Сигнал посылается всем процессам, кому можно, кроме PID=1 (init)\n");
 		} else {
 			printf("Сигнал посылается всем, чья pgroup = %d\n", validkillpid);
 		}
 		
 		if(signo==0){
 			printf("Сигнал не посылается, но проверяется возможность доставки сигнала\n");
 		} else if(signo>0){
 			printf("Посылается сигнал с требуемым номером %d\n", signo);
 		} else {
 			perror("Сигнал меньше нуля\n");
 			exit(1);
 		}
 		
 		if (kill(validkillpid, signo) == -1){
 			perror("kill err\n"); 
 			exit(1)); 
 		} 
 		
 		exit(0); 
}
