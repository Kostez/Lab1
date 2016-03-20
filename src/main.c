#include <getopt.h>

struct params {
	modes_lab1 mode;
	int amount;
	int signalname;
	
	
	
} params_lab1;

enum modes {
	std = 0,
	child,
	posix,
	kill,
	pipe
} modes_lab1;

int main(int argc, char *argv[]) {
	
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
				
				break;
			};
			case 'a': {
				
				break;
			};
			case 's': {
				
				break;
			};
			case 'p': {
				
				break;
			};
			
			
			
		}
  
  
  
  
  
}
