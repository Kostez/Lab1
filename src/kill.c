#include <general.h>

void mode_kill(int signo, int validkillpid){		
 		kill(validkillpid, signo);
}
