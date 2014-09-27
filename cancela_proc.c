#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
 struct msgp{
 	long mtype;
 	time_t tempo;
 	char mtext[4];
 };

typedef struct msgp Buff;
int main(int argc,char* argv[]){
	int idfila;
	if(argc!=2){
		printf("Numero de argumentos invalido!");
	}
	if (idfila = msgget(110143566, 0x1FF) < 0)
		{
		printf("erro na obtencao da fila\n");
		exit(1);
		}
	Buff* msg = (Buff*)malloc(sizeof(Buff*));
	msg->mtype = 4;
	strcpy(msg->mtext,argv[1]);
	msgsnd(idfila,msg,sizeof(Buff) - 4,0);
	printf("Mensagem de terminar processo %s enviada! \n",argv[1]);
	return 0;
}
