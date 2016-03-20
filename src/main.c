#include <getopt.h>

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
				printf("This is demo help. Try -h or --help.\n");
				printf("option_index = %d (\"%s\",%d,%c)\n",
					option_index,
					long_options[option_index].name,
					long_options[option_index].has_arg,
					long_options[option_index].val
				);
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
