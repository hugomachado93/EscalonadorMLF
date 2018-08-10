	#include <sys/wait.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	
	//programa-usuario usado apenas para criar um processo
	int main(int argc, char* argv[])
	{
		int i,w4IO;
		
		int rajada1;
		
		rajada1 = atoi(argv[1]);
		
		for(i = 0;i<rajada1;i++){ 
			fprintf(stdout,"%d\n", getpid());
			sleep(1);
		}
		
		
		
		
	return 0;
	}
