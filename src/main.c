#include <getopt.h>

int main(int argc, char *argv[]) {
  
  const char* modes[] = {"std", "child", "posix", "kill", "pipe"};
  
  const struct option long_options[] = {
		{"help",no_argument,NULL,'h'},
		{"size",optional_argument,NULL,'s'},
		{"file",required_argument,NULL,'f'},
		{NULL,0,NULL,0}
	};
  
  
  
  
  
  
}
