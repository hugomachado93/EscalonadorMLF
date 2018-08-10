	#include <sys/wait.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	
	//programa-usuario usado apenas para criar um processo
	int main(int argc, char* argv[])
	{
		int i,w4IO;
		
		int rajada1, rajada2, rajada3;
		
		rajada1 = atoi(argv[1]);
		rajada2 = atoi(argv[2]);
		rajada3 = atoi(argv[3]);
		
		for(i = 0;i<rajada1;i++){ 
			fprintf(stdout,"%d\n", getpid());
			sleep(1);
		}
		
		kill(getppid(), SIGUSR1);
		
		for(i = 0;i<rajada2;i++){ 
			fprintf(stdout,"%d\n", getpid());
			sleep(1);
		}
		
		kill(getppid(), SIGUSR1);
		
		for(i = 0;i<rajada3;i++){ 
			fprintf(stdout,"%d\n", getpid());;
			sleep(1);
		}
		
	return 0;
	}
