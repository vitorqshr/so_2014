#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <signal.h>
 struct msgp{
 	long mtype;
 	time_t tempo;
 	int pid;
 	int vezes;
 };

typedef struct msgp Buff;
int main(int argc,char* argv[]){
	if(argc<3){
		printf("Numero de argumentos invalido!");
		exit(1);
	}
	//verifica se a prioridade é válida
	if((atoi(argv[2])<1) || (atoi(argv[2])>3)){
		printf("Erro! Prioridade inválida! \n");
		exit(2);
	}
	int idfila;
	Buff* msg = (Buff*)malloc(sizeof(Buff*));
	if (idfila = msgget(110143566, 0x1FF) < 0)
		{
		printf("erro na obtencao da fila\n");
		exit(1);
		}
	int i,pid;
	//cria uma matriz de caracter auxiliar para guardas os argumentos do programa que será executado
	char **aux;
	//aloca-se o vetor aux
	aux = (char**) malloc ((argc-2)*sizeof(char*));
	for(i=0;i<(argc-2);i++){
		aux[i] = (char *) malloc (100);
		aux[i][0] = '\0';
	}
	//passa os argvs para o vetor aux
	for(i=0;i<(argc-2);i++){
		strcpy(aux[i],argv[i+2]);
	}
	//verifica se foi passado corretamente
	for(i=0;i<(argc-2);i++){
		printf("%s \n",aux[i]);
	}
	if((pid = fork())<0){
		printf("Erro no fork! \n");
		exit(1);
	}
	//se for o filho executa o programa
	if(pid == 0){
		execv(argv[1],aux);
	}else{
		//se for o pai manda mensagem na fila sinalizando que um novo processo foi criado
		msg->mtype = atoi(argv[2]);
		msg->pid = pid;
		msg->vezes = 0;
		msg->tempo = time(NULL);
		msgsnd(idfila,msg,sizeof(Buff) - 4,0);
		printf("Mensagem enviada!\n");
		//o processo inicia parado, só vai executar pelo execprod quando for a vez dele
		kill(pid,SIGTSTP);
	}
	return 0;
}
