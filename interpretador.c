#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>

#define SHSIZE 100

int main()
{
	int i,j=0, quant;
	int *pid;
	char nome[100];
	char comando[100];
	int *raj;
	int segmento;
	int segmento2;
	int segmento3;
	int status;
	key_t key;
	key_t key2;
	key_t key3;
	key = 1000;
	key2 = 2000;
	key3 = 50;
	char *param;
	int rajada1, rajada2, rajada3 , rajada4 , rajada5;
	
	//passa as rajadas pela memoria comparrtilhada
	// aloca a memória compartilhada
	segmento = shmget (key, SHSIZE, IPC_CREAT | 0666);
	// associa a memória compartilhada ao processo
	param = (char *) shmat (segmento, 0, 0);
	
	//pega o pid do pai para poder enviar um sinal
	// aloca a memória compartilhada
	segmento2 = shmget (key2, sizeof(int), IPC_CREAT | 0666);
	// associa a memória compartilhada ao processo
	pid = (int*) shmat (segmento2, 0, 0);

	segmento3 = shmget (key3, sizeof(int), IPC_CREAT | 0666);
	// associa a memória compartilhada ao processo
	raj = (int*) shmat (segmento3, 0, 0);
	*raj = 0;
		//Executa forever
		while(1){
			//param = "0";
			//colocar os tempos de rajada no formato por exemplo 005 010 007 cada bloco é uma rajada
			scanf("%d %[^\n]%*c", raj ,  param);
			if (*raj <= 0){
				printf("Digitou numero de rajadas invalidas ou rajadas invalida\n Saindo do programa...");
				exit(0);	
			}
			
			rajada1 = atoi(&param[0]);
			rajada2 = atoi(&param[4]);
			rajada3 = atoi(&param[7]);
			rajada4 = atoi(&param[10]);
			rajada5 = atoi(&param[13]);
			
			if(rajada1 < 0 || rajada2 < 0 || rajada3 < 0 || rajada4 < 0 || rajada5 < 0){
				printf("Digitou valor de rajada errado");
				exit(0);
			}
			
			kill(*pid, SIGUSR2);
			if(strcmp(param, "quit")==0){
				//Sai do programa
				exit(0);
			}
			//printf("%d %d %d", rajada1, rajada2, rajada3);
		}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Libera memoria compartilhada do processo
shmdt(param);
shmdt(pid);
shmdt(raj);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Libera memoria compartilhada
shmctl(segmento, IPC_RMID, 0);
shmctl(segmento2, IPC_RMID, 0);
shmctl(segmento3, IPC_RMID, 0);
	
return 0;
}
	
		

	
