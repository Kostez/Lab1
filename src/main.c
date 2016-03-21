#include <stdio.h>
#include <getopt.h>

enum Modes_e {
	std = 0,
	child,
	posix,
	kill,
	pipe
};

struct Params_s {
	enum Modes_s mode;
	int amount;
	int signalname;
	int pid;
};

int main(int argc, char *argv[]) {
	
	struct Params_s param;
	
	const char* short_options = "m:a::s::p::";
	const char* modes[] = {"std", "child", "posix", "kill", "pipe"};
	
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
				for(int i = 0; i < 4; i++) {
					if(strcmp(modes[i], optarg) == 0) {
						param.mode = i;
						break;
					}
				}
				break;
			};
			case 'a': {
				printf("Case a \n");
				param.amount = atoi(optarg);
				break;
			};
			case 's': {
				printf("Case s \n");
				param.signalname = atoi(optarg);
				break;
			};
			case 'p': {
				printf("Case p \n");
				param.pid = atoi(optarg);
				break;
			};
	}
}
