#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 struct msgp{
 	long mtype;
 	char mtext[4];
 };

typedef struct msgp Buff;
int main(){
	int idfila;
	//cria a fila
	if ((idfila = msgget(110143566, IPC_CREAT | 0x1FF)) < 0)
	{
	printf("erro na criacao da fila\n");
	exit(1);
	}
	Buff* msg = (Buff*)malloc(sizeof(Buff*));
	int recebeu_execproc=0,recebeu_termina=0,recebeu_cancela=0;
	int proc,i;
	char aux[5];
	while(1){
		//recebe termino de execprodc
		if((recebeu_execproc = msgrcv(idfila,msg,4,9,IPC_NOWAIT)) >0 ){
			printf("Terminando execprocd \n");
			exit(9);
		}
		//recebe cancelamento
		if((recebeu_execproc = msgrcv(idfila,msg,4,4,IPC_NOWAIT)) >0){
			for(i=0;i<4;i++){
				aux[i] = msg->mtext[i];
			}
			aux[5] = '\0';
			proc = atoi(aux);
			printf("Recebeu mensagem de cancelamento do processo de processo :%d \n",proc);
		}
		//recebe processo
		if((recebeu_execproc = msgrcv(idfila,msg,4,1,IPC_NOWAIT))>0){
			for(i=0;i<4;i++){
				aux[i] = msg->mtext[i];
			}
			aux[5] = '\0';
			proc = atoi(aux);
			printf("Recebeu mensagem de criacao do processo de prioridade 1 :%d \n",proc);
		}

	}
	return 0;
}
