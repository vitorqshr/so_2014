1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
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
