#include <getopt.h>

int main(int argc, char *argv[]) {
	const char* modes[] = {"std", "child", "posix", "kill", "pipe"};
	
	const struct option long_options[] = {
		{"mode",required_argument,NULL,'m'},
		{"amount",optional_argument,NULL,'a'},
		{"signal",optional_argument,NULL,'s'},
		{"pid",optional_argument,NULL,'p'},
	};
  
  
  
  
  
  
}
