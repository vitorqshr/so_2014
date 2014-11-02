#include <stdio.h>
#include <stdlib.h>
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
int main(){
    time_t tempo_atual;
    time_t tempo_inicial_quantum;
    time_t tempo_atual_quantum;
    double dif;
    int idfila;
    int aux_prioridade;
    srand(time(NULL));
    //cria a fila
    if ((idfila = msgget(110143566, IPC_CREAT | 0x1FF)) < 0)
    {
    printf("erro na criacao da fila\n");
    exit(1);
    }
    Buff* msg = (Buff*)malloc(sizeof(Buff*));
    int recebeu_execproc=0,recebeu_termina=0,recebeu_cancela=0;
    int i;
    char aux[5];
    while(1){
        tempo_atual = time(NULL);
        //recebe termino de execprodc
        if((recebeu_execproc = msgrcv(idfila,msg,sizeof(Buff) - 4,9,IPC_NOWAIT)) >0 ){
            printf("Terminando execprocd \n");
            //termina todos os processos
            while((recebeu_execproc = msgrcv(idfila,msg,sizeof(Buff) - 4,1,IPC_NOWAIT)) >0){
                kill(msg->pid,SIGKILL);
            }
            while((recebeu_execproc = msgrcv(idfila,msg,sizeof(Buff) - 4,2,IPC_NOWAIT)) >0){
                kill(msg->pid,SIGKILL);
            }
            while((recebeu_execproc = msgrcv(idfila,msg,sizeof(Buff) - 4,3,IPC_NOWAIT)) >0){
                kill(msg->pid,SIGKILL);
            }
            //remove a fila
            msgctl(idfila,IPC_RMID,NULL);
            exit(9);
        }
        //recebe cancelamento
        if((recebeu_execproc = msgrcv(idfila,msg,sizeof(Buff) - 4,4,IPC_NOWAIT)) >0){
            printf("Recebeu mensagem de cancelamento do processo de pid :%d \n",msg->pid);
            kill(msg->pid,SIGKILL);
        }
        //recebe processo
        if((recebeu_execproc = msgrcv(idfila,msg,sizeof(Buff) - 4,1,IPC_NOWAIT))>0){
            tempo_inicial_quantum = time(NULL);
            tempo_atual_quantum = time(NULL);
            //inicia o processo
            kill(msg->pid,SIGCONT);
            printf("Recebeu mensagem de criacao do processo de prioridade 1 :%d \n",msg->pid);
            //execute este loop deixando o processo rodar por 10 segundos...
            while(difftime(tempo_atual_quantum,tempo_inicial_quantum)<10){
                //printf("%.f \n", difftime(tempo_atual_quantum,msg->tempo));
                tempo_atual_quantum = time(NULL);
            }
            msg->vezes = msg->vezes + 1;
            //se já tiver executado 4 vezes nesta priorirade, inicia uma nova com prioridade aleatória
            if(msg->vezes >= 4){
                msg->vezes = 0;
                msg->mtype = (rand()%3)+1;
                msgsnd(idfila,msg,sizeof(Buff) - 4,0);
            }else{
                msgsnd(idfila,msg,sizeof(Buff) - 4,0);
            }
            printf("Parando processo %d \n",msg->pid);
            kill(msg->pid,SIGTSTP);
            //printf("Recebeu mensagem de criacao do processo de prioridade 1 :%d \n",msg->pid);
            //mostra a quanto tempo cada processo está rodando, somente usar para debugar pois aparecem muitas mensagens ao msm tempo
            //printf("Este processo esta rodando a %.f segundos \n",difftime(tempo_atual,msg->tempo));
            //coloca novamente a mensagem na fila
            //msgsnd(idfila,msg,sizeof(Buff) - 4,0);
        }else if((recebeu_execproc = msgrcv(idfila,msg,sizeof(Buff) - 4,2,IPC_NOWAIT))>0){
            tempo_inicial_quantum = time(NULL);
            tempo_atual_quantum = time(NULL);
            //inicia o processo
            kill(msg->pid,SIGCONT);
            printf("Recebeu mensagem de criacao do processo de prioridade 1 :%d \n",msg->pid);
            //execute este loop deixando o processo rodar por 10 segundos...
            while(difftime(tempo_atual_quantum,tempo_inicial_quantum)<10){
                //printf("%.f \n", difftime(tempo_atual_quantum,msg->tempo));
                tempo_atual_quantum = time(NULL);
            }
            msg->vezes = msg->vezes + 1;
            //se já tiver executado 4 vezes nesta priorirade, inicia uma nova com prioridade aleatória
            if(msg->vezes >= 4){
                msg->vezes = 0;
                msg->mtype = (rand()%3)+1;
                msgsnd(idfila,msg,sizeof(Buff) - 4,0);
            }else{
                msgsnd(idfila,msg,sizeof(Buff) - 4,0);
            }
            printf("Parando processo %d \n",msg->pid);
            kill(msg->pid,SIGTSTP);
            //printf("Recebeu mensagem de criacao do processo de prioridade 1 :%d \n",msg->pid);
            //mostra a quanto tempo cada processo está rodando, somente usar para debugar pois aparecem muitas mensagens ao msm tempo
            //printf("Este processo esta rodando a %.f segundos \n",difftime(tempo_atual,msg->tempo));
            //coloca novamente a mensagem na fila
            //msgsnd(idfila,msg,sizeof(Buff) - 4,0);
        }else if((recebeu_execproc = msgrcv(idfila,msg,sizeof(Buff) - 4,3,IPC_NOWAIT))>0){
            tempo_inicial_quantum = time(NULL);
            tempo_atual_quantum = time(NULL);
            //inicia o processo
            kill(msg->pid,SIGCONT);
            printf("Recebeu mensagem de criacao do processo de prioridade 1 :%d \n",msg->pid);
            //execute este loop deixando o processo rodar por 10 segundos...
            while(difftime(tempo_atual_quantum,tempo_inicial_quantum)<10){
                //printf("%.f \n", difftime(tempo_atual_quantum,msg->tempo));
                tempo_atual_quantum = time(NULL);
            }
            msg->vezes = msg->vezes + 1;
            //se já tiver executado 4 vezes nesta priorirade, inicia uma nova com prioridade aleatória
            if(msg->vezes >= 4){
                msg->vezes = 0;
                msg->mtype = (rand()%3)+1;
                msgsnd(idfila,msg,sizeof(Buff) - 4,0);
            }else{
                msgsnd(idfila,msg,sizeof(Buff) - 4,0);
            }
            printf("Parando processo %d \n",msg->pid);
            kill(msg->pid,SIGTSTP);
            //printf("Recebeu mensagem de criacao do processo de prioridade 1 :%d \n",msg->pid);
            //mostra a quanto tempo cada processo está rodando, somente usar para debugar pois aparecem muitas mensagens ao msm tempo
            //printf("Este processo esta rodando a %.f segundos \n",difftime(tempo_atual,msg->tempo));
            //coloca novamente a mensagem na fila
            //msgsnd(idfila,msg,sizeof(Buff) - 4,0);
        }

    }
    return 0;
}
