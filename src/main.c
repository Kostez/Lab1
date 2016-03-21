#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

/*
 * 
 */

enum Modes {
	modes_std = 1,
	modes_child,
	modes_posix,
	modes_kill,
	modes_pipe
}modes_e;

struct Params {
	enum Modes modes_e;
	int amount;
	int signalname;
	int pid;
}params;

int main(int argc, char** argv) {

    const char* short_options = "m:a::s::p::";
    const char *modes[] = {"std", "child", "posix", "kill", "pipe"};
	
    const struct option long_options[] = {
	{"mode",required_argument,NULL,'m'},
	{"amount",optional_argument,NULL,'a'},
	{"signal",optional_argument,NULL,'s'},
	{"pid",optional_argument,NULL,'p'},
    };
	
    int rez;
    int option_index;
    
    while ((rez=getopt_long(argc,argv,short_options,
		long_options,&option_index))!=-1){
	switch(rez){
            case 'm': {
		printf("Case m \n");
                int i = 0;
		for(; i < 5; i++) {
                    if(strcmp(modes[i], optarg) == 0) {
                        params.modes_e = i;
                        break;
                    }
		}
		break;
            };
            case 'a': {
                printf("Case a \n");
		params.amount = atoi(optarg);
		break;
            };
            case 's': {
                printf("Case s \n");
		params.signalname = atoi(optarg);
		break;
            };
            case 'p': {
                printf("Case p \n");
		params.pid = atoi(optarg);
		break;
            };
	}
    }
    
    return 0;
}
