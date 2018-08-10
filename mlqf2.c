#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define SHSIZE 100
#define ESPERA 1500
struct processo {
	pid_t pid;
	pid_t pidFilho;
}; typedef struct processo Processo;

void addProc(int sinal);
void w4io(int sinal2);
void andaFila(int *pids);
void andaFila2(int *pids);
void andaFila3(int *pids);
void paraTodos(int *pids);
void processoAcaba(int sinal);
//variaveis globais declaradas//////////////////////////////////
int status;
int *addProcesso;
int *wait4io=0;
int interrompe = 0;
int *j;
int *j2;
int *j3;
int *filaPid;
int *filaPid2;
int *filaPid3;
int *filaPidParado;
int *numFila;
int *contador;
int *io;
int *raj;
int *f1,*f2,*f3;

int main(int argc, char *argv[])
{
//variaveis declaradas///////////////////////////////////////
	char *old;
	int segmento;
	int segmento2;
	int segmento3;
	int shmid;
	int shmid2;
	int shmid3;
	int segmento4;
	int segmento5;
	int segmento6;
	int segmento7;
	int segmento8;
	int segmento9;
	int segmento10;
	int segmento11;
	int segmento12;
    int segmento13;
    int segmento14;
    int segmento15;
    int segmento16;
	int *pid;
	int quantum;
	pid_t waitpid2;
	pid_t waitPid;
	key_t key;
	key_t key2;
	key_t key3;
	key_t key4;
	key_t key5;
	key_t key6;
	key_t key7;
    key_t key8;
	key = 1000;
	key2 = 2000;
	key3 = 3000;
	key4 = 4000;
	key5 = 5000;
	key6 = 6000;
	key7 = 7000;
    key8 = 50;
	Processo *p;
	int i=0,k=0;
	char *param;
	int sum = 0;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//act para que o SIGCHLD envie um sinal apenas quando o programa parar
	struct sigaction act;

	act.sa_handler = processoAcaba;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDSTOP;
	
//alocação de memoria compartilhada///////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////
	segmento = shmget (key, SHSIZE, IPC_CREAT | 0666);
	param = (char *) shmat (segmento, 0, 0);
	//////////////////////////////////////////////////////////

	segmento2 = shmget (key2, sizeof(int), IPC_CREAT | 0666);
	pid = (int*) shmat (segmento2, 0, 0);
	*pid = getpid();
	//////////////////////////////////////////////////////////
	segmento3 = shmget (key3, sizeof(int), IPC_CREAT | 0666);
	addProcesso = (int*) shmat (segmento3, 0, 0);
	*addProcesso = 0;
	//////////////////////////////////////////////////////////
	segmento4 = shmget (key4, sizeof(int), IPC_CREAT | 0666);
	wait4io = (int*) shmat (segmento4, 0, 0);
	*wait4io = 0;
	//////////////////////////////////////////////////////////
	shmid = shmget (4325, 10*sizeof(int), IPC_CREAT | 0666);
	filaPid = (int*) shmat (shmid, 0, 0);
	//////////////////////////////////////////////////////////
	shmid = shmget (4326, 10*sizeof(int), IPC_CREAT | 0666);
	filaPid2 = (int*) shmat (shmid, 0, 0);
	//////////////////////////////////////////////////////////
	shmid = shmget (4327, 10*sizeof(int), IPC_CREAT | 0666);
	filaPid3 = (int*) shmat (shmid, 0, 0);
	//////////////////////////////////////////////////////////
    segmento13 = shmget (key8, sizeof(int), IPC_CREAT | 0666);
	raj = (int*) shmat (segmento13, 0, 0);
	//////////////////////////////////////////////////////////
	segmento5 = shmget (key5, sizeof(int), IPC_CREAT | 0666);
	j = (int*) shmat (segmento5, 0, 0);
	*j=0;
	//////////////////////////////////////////////////////////
	segmento8 = shmget (9000, sizeof(int), IPC_CREAT | 0666);
	j2 = (int*) shmat (segmento8, 0, 0);
	*j2=0;
	//////////////////////////////////////////////////////////
	segmento9 = shmget (8000, sizeof(int), IPC_CREAT | 0666);
	j3 = (int*) shmat (segmento9, 0, 0);
	*j3=0;
	//////////////////////////////////////////////////////////
	segmento7 = shmget (key7, sizeof(int) , IPC_CREAT | 0666);
	io = (int*) shmat (segmento7, 0 ,0);
	*io = 0;
	//////////////////////////////////////////////////////////
	segmento6 = shmget (key6, sizeof(int), IPC_CREAT | 0666);
	numFila = (int*) shmat (segmento6, 0, 0);
	*numFila = 1;
  	//////////////////////////////////////////////////////////
  	segmento14 = shmget (14000, sizeof(int), IPC_CREAT | 0666);
	f1 = (int*) shmat (segmento14, 0, 0);
	//////////////////////////////////////////////////////////
	segmento15 = shmget (15000, sizeof(int), IPC_CREAT | 0666);
	f2 = (int*) shmat (segmento15, 0, 0);
	//////////////////////////////////////////////////////////
	segmento16 = shmget (16000, sizeof(int), IPC_CREAT | 0666);
	f3 = (int*) shmat (segmento16, 0, 0);
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Verifica se ao criar memoria compartilhada nao ocorreu nenhum erro
		if (shmid == -1 || shmid2 == -1 || shmid == -1 || segmento == -1 || segmento2 == -1 || segmento3 == -1 || segmento4 == -1 || segmento5 == -1 ||segmento6 == -1 || segmento7 == -1 || segmento8 == -1 || segmento9 == -1 || segmento10 == -1 || segmento11 == -1 || segmento12 == -1 || segmento13 == -1 || segmento14 == -1 || segmento15 == -1 || segmento16 == -1) {
      	perror("Erro ao criar a memoria compartilhada");
      	return EXIT_FAILURE;
  	}

//fim alocação memoria compartilhada

	//cria structs para os processos
	 
	
	p = (Processo*)malloc(10*sizeof(Processo));
	
	//inicializa o pidFilho com -100 para não atrapalhar no sigstop
	for(i=0;i<10;i++){
		filaPid[i] = -100;
	}
	
	for(i=0;i<10;i++){
		filaPid2[i] = -100;
	}
	
	for(i=0;i<10;i++){
		filaPid3[i] = -100;
	}
	////////////////////////////////////////////////////////////////////
	//Sinais
	if(signal(SIGUSR2, addProc)==SIG_ERR){
		fprintf(stdout, "erro ao receber sinal\n");
	}

	if(signal(SIGUSR1, w4io)==SIG_ERR){
		fprintf(stdout, "erro ao receber sinal\n");
	}
	if(sigaction(SIGCHLD, &act, 0)<0){
		fprintf(stdout, "erro ao receber sinal\n");
	}
	/////////////////////////////////////////////////////////////////
			if((p[*j].pid = fork())==0){
				while(1){
					//Qual fila vai ser executada
					if(*j>=1){
						*numFila = 1;
						kill(filaPid[0], SIGCONT);
						kill(filaPid2[0], SIGSTOP);
						kill(filaPid3[0], SIGSTOP);
					}else if(*j2 >= 1 && *j<1){
						*numFila = 2;
						kill(filaPid2[0], SIGCONT);
						kill(filaPid[0], SIGSTOP);
						kill(filaPid3[0], SIGSTOP);
					}else if(*j3 >= 1 && *j<1 && *j2<1){
						*numFila = 3;
						kill(filaPid3[0], SIGCONT);
						kill(filaPid[0], SIGSTOP);
						kill(filaPid2[0], SIGSTOP);
					}
					
					
					////////////////////////////////////////
					if(*addProcesso){
						if((p[*j].pidFilho = fork()) == 0){
							//Seleciona o programa usuario
							if ( *raj == 1){
                    			execl("programa-usuario5", "Trabalho01", &param[0], NULL);
                            } else if ( *raj == 2){
                          		execl("programa-usuario4", "Trabalho01", &param[0], &param[4],  NULL);              
                           	} else if ( *raj == 3){
                         		execl("programa-usuario3", "Trabalho01", &param[0], &param[4], &param[7] ,  NULL); 
                            } else if ( *raj == 4){
                         		execl("programa-usuario2", "Trabalho01", &param[0], &param[4], &param[7], &param[10], NULL);  
                            } else if ( *raj == 5){
                         		execl("programa-usuario1", "Trabalho01", &param[0], &param[4], &param[7],&param[10], &param[13] , NULL); 
                           	} 
						}else{
							fprintf(stdout, "Entrou novo processo\n");
							//adiciona um pequena antes de para o proximo processo da fila
							usleep(ESPERA);
							kill(p[*j].pidFilho, SIGSTOP);
							*addProcesso = 0;
							//todo novo processo entra parado esperando sua vez na fila
							filaPid[*j] = p[*j].pidFilho;
							//aumenta o tamanho da fila para alocar o proximo processo
							(*j)++;
						}
					}

				}		
			}else{
				//IO
				if((waitPid = fork())==0){
					while(1){
						//Processo que vai tratar o IO
						if(*wait4io){
							if(*numFila == 1){
								if((waitpid2 = fork()) == 0){
										int var;
										int temp;
										int k;
										temp = filaPid[0];
										fprintf(stdout, "Processo %d entrou em IO\n", filaPid[0]);
										kill(filaPid[0] , SIGSTOP);
										*f2=0;
										//Quando tiver apenas um unico processo
										andaFila(filaPid);
										//Diminui o tamanho da fila até que o processo retorne a fila
										(*j)--;
										sleep(3);
										//Processo em IO retorna a fila
										(*j)++;
										if(*j==1){
											*f1=0;
										}
										k=*j;
										filaPid[k-1] = temp;
									}
								}else if(*numFila == 2){
									if((waitpid2 = fork()) == 0){
										int var;
										int temp;
										int k;
										temp = filaPid2[0];
										fprintf(stdout, "Processo %d entrou em IO\n", filaPid2[0]);
										kill(filaPid2[0] , SIGSTOP);
										*f2=0;
										//Quando tiver apenas um unico processo
										if(*j2==1){
											//filaPid2[0] = -1111;
										}
										andaFila(filaPid2);
										//Diminui o tamanho da fila até que o processo retorne a fila
										(*j2)--;
										sleep(3);
										//Processo em IO retorna a fila
										(*j2)++;
										if(*j2==1){
											*f2=0;
										}
										k=*j2;
										filaPid2[k-1] = temp;
									}
								}
								*wait4io = 0;
						}
					}
					//Pai que gerencia os filhos de acordo com a fila
				}else{
					while(1){
					//aguardando que o processo inicie
						if(*addProcesso){
							while(1){
								if(*numFila == 1){
									inicio:
									sleep(1);
									for(*f1=0;*f1<10;(*f1)++){
										//Para que o processo nao fique preso no loop
										if(*j<1 && *j2 >0){
											goto inicio2;
										}else if(*j<1 && *j2 < 1 && *j3 >0){
											goto inicio3;
										}
										fprintf(stdout, "Fila 1: %d Fila 2: %d Fila 3: %d %d\n", *j,*j2, *j3, *f1);
										if(*io){
											*wait4io = 1;
											fprintf(stdout, "mantem na fila 1\n");
											*io=0;
											goto inicio;
										}
										sleep(1);
									}
									//Caso o processo termine no meio de uma rajada

									//Cair de fila
									if(*io==0){
											fprintf(stdout, "cai para fila 2\n");
											kill(filaPid[0], SIGSTOP);
											filaPid2[*j2] = filaPid[0];
											andaFila(filaPid);
											(*j2)++;
											(*j)--;
											if(*j<1){
												goto inicio2;
											}
									}

								}else if(*numFila == 2){
									inicio2:
									for(*f2=0;*f2<15;(*f2)++){
										fprintf(stdout, "Fila 1: %d Fila 2: %d Fila 3: %d %d\n", *j,*j2, *j3, *f2);
										//Para que o processo nao fique preso no loop
										if(*j2<1 && *j3 >0 && *j<1){
											goto inicio3;
										}else if(*j>0){
											goto inicio;
										}
										if(*io){
											fprintf(stdout, "Sobe para fila 1\n");
											kill(filaPid2[0], SIGSTOP);
											filaPid[*j] = filaPid2[0];
											andaFila2(filaPid2);
											(*j)++;
											(*j2)--;
											*io=0;
											//envia o sinal denovo para que de tempo das filas serem trocadas
											*numFila=1;
											*wait4io=1;
											//Vai apra fila 1
										}
										sleep(1);
									}
									//Caso o processo termine no meio de uma rajada

									//Cair de fila
									if(*io==0){
										fprintf(stdout, "cai para fila 3\n");
										kill(filaPid2[0], SIGSTOP);
										filaPid3[*j3] = filaPid2[0];
										andaFila2(filaPid2);
										(*j3)++;
										(*j2)--;
										if(*j2<1 && *j<1){
											goto inicio3;
										}
									}
								}else if(*numFila == 3){
									inicio3:
									for(*f3=0;*f3<20;(*f3)++){
										//Para que o processo nao fique preso no loop
										if(*j2>0){
											goto inicio2;
										}else if(*j>0){
											goto inicio;
										}
										fprintf(stdout, "Fila 1: %d Fila 2: %d Fila 3: %d %d\n", *j,*j2, *j3, *f3);
										if(*io){
											fprintf(stdout, "Sobe para fila 2\n");
											kill(filaPid3[0], SIGSTOP);
											filaPid2[*j] = filaPid3[0];
											andaFila3(filaPid3);
											(*j2)++;
											(*j3)--;
											*io=0;
											//Vai para a fila 2
											*numFila=2;
											*wait4io=1;
											goto inicio2;
										}
										sleep(1);
									}
									if(*io==0){
										//fprintf(stdout, "mantem na fila 3\n");
										andaFila3(filaPid3);
										goto inicio3;
									}
								}
						
							}
						}
					}
				}
			}
////////////////////////////////////////////////////////////////////////////////////////
//Libeara memoria compartilhada do processo
shmdt(param);
shmdt(pid);
shmdt(addProcesso);
shmdt(wait4io);
shmdt(filaPid);
shmdt(filaPid2);
shmdt(filaPid3);
shmdt(raj);
shmdt(j);
shmdt(j2);
shmdt(j3);
shmdt(io);
shmdt(numFila);
shmdt(f1);
shmdt(f2);
shmdt(f3);
/////////////////////////////////////////////////////////////////////////////////////////////
//Libera memoria compartilhada
shmctl(shmid, IPC_RMID, 0);
shmctl(shmid2, IPC_RMID, 0);
shmctl(shmid3, IPC_RMID, 0);
shmctl(segmento, IPC_RMID, 0);
shmctl(segmento2, IPC_RMID, 0);
shmctl(segmento3, IPC_RMID, 0);
shmctl(segmento4, IPC_RMID, 0);
shmctl(segmento5, IPC_RMID, 0);
shmctl(segmento6, IPC_RMID, 0);
shmctl(segmento7, IPC_RMID, 0);
shmctl(segmento8, IPC_RMID, 0);
shmctl(segmento9, IPC_RMID, 0);
shmctl(segmento10, IPC_RMID, 0);
shmctl(segmento11, IPC_RMID, 0);
shmctl(segmento12, IPC_RMID, 0);
shmctl(segmento13, IPC_RMID, 0);
shmctl(segmento14, IPC_RMID, 0);
shmctl(segmento15, IPC_RMID, 0);
shmctl(segmento16, IPC_RMID, 0);
/////////////////////////////////////////////////////////////////////////////////////////////////
return 0;
}
//função para andar na fila
void andaFila(int *pids){
	int i;
	int k;
	int temp;
	temp = pids[0];
	k = *j;
	for(i=0;i<k-1;i++){
		pids[i] = pids[i+1];
	}
	pids[k-1] = temp;
}
//função para andar na fila2
void andaFila2(int *pids){
fprintf(stdout, "anda\n");
	int i;
	int k;
	int temp;
	temp = pids[0];
	k = *j2;
	for(i=0;i<k-1;i++){
		pids[i] = pids[i+1];
	}
	pids[k-1] = temp;
}
//função para andar na fila3
void andaFila3(int *pids){
	int i;
	int k;
	int temp;
	temp = pids[0];
	k = *j3;
	for(i=0;i<k-1;i++){
		pids[i] = pids[i+1];
	}
	pids[k-1] = temp;
}
//para todos os processos que nao seja o primeiro
void paraTodos(int *pids){
	int i;
	for(i=1;i<10;i++){
		kill(pids[i], SIGSTOP);
	}
}

void processoAcaba(int sinal){
	//Retira o processo do sistema
	fprintf(stdout, "Processo saiu\n");
	if(*numFila == 1){
		andaFila(filaPid);
		(*j)--;
		*f1=0;
	}else if(*numFila == 2){
		andaFila2(filaPid2);
		(*j2)--;
		*f2=0;
	}else if(*numFila == 3){
		andaFila3(filaPid3);
		(*j3)--;
		*f3=0;
	}
}

//sinal dizendo que a rajada acabou
void w4io(int sinal2){
	*io = 1;
}

//recebe o sinal para colocar os processos na fila
void addProc(int sinal){
	*addProcesso = 1;
}



