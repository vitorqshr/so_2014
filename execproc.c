#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 struct msgp{
 	long mtype;
 	char mtext[4];
 };

typedef struct msgp Buff;
int main(int argc,char* argv[]){
	if(argc<3){
		printf("Numero de argumentos invalido!");
		exit(1);
	}
	int idfila;
	Buff* msg = (Buff*)malloc(sizeof(Buff*));
	if (idfila = msgget(110143566, 0x1FF) < 0)
		{
		printf("erro na obtencao da fila\n");
		exit(1);
		}
	int i,pid;
	char **aux;
	aux = (char**) malloc ((argc-2)*sizeof(char*));
	for(i=0;i<(argc-2);i++){
		aux[i] = (char *) malloc (100);
		aux[i][0] = '\0';
	}
	strcpy(aux[0],argv[1]);
	for(i=1;i<(argc-2);i++){
		strcpy(aux[i],argv[i+2]);
	}
	for(i=0;i<(argc-2);i++){
		printf("%s \n",aux[i]);
	}
	if((pid = fork())<0){
		printf("Erro no fork! \n");
		exit(1);
	}
	if(pid == 0){
		execv(argv[1],aux);
	}else{
		char auxmsg[4];
		msg->mtype = 1;
		snprintf(auxmsg, 4,"%d",pid);
		strcpy(msg->mtext,auxmsg);
		msgsnd(idfila,msg,4,0);
		printf("Mensagem enviada!\n");
	}
	return 0;
}
