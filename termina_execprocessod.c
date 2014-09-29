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
 	int pid;
 	int vezes;
 };

typedef struct msgp Buff;
int main(){
	int idfila;
	if ((idfila = msgget(110143566, 0x1FF)) < 0)
		{
		printf("erro na obtencao da fila\n");
		exit(1);
		}

	Buff* msg = (Buff*)malloc(sizeof(Buff*));
	msg->mtype = 9;
	msg->pid = 0;
	msgsnd(idfila,msg,sizeof(Buff) - 4,0);
	printf("Mensagem de terminar execprocd enviada! \n");
	return 0;
}
