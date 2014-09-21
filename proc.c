#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]){
	int i=0;
	printf("Executando \n");
	printf("Argumentos = %d \n",argc);
	for(i=0;i<argc;i++){
		printf("%s\n", argv[i]);
	}
	while(i>=0){
		i++;
	}
	return 0;
}
