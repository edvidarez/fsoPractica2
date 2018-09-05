#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>


void writeShutdown(){
	FILE* file = fopen("shutdown.txt", "w");
	fprintf(file, "shutdown\n");
}

int main()
{
	char input[1000];

	

	while(1){
		//execlp("clear", "clear",NULL);
		printf(">>");
		fgets(input,1000,stdin);
		//printf("%s\n",input );
		if(strcmp(input,"exit\n")==0){
			//printf("Exit\n");
			exit(0);
		} 
		if(strcmp(input,"shutdown\n")==0){
			writeShutdown();
			exit(1);
		}

		char *argumentos[100];

		char * pch;
		pch = strtok (input," \n\0");
		int k = 0;
		while (pch != NULL)
		{
			argumentos[k++] = pch;
			pch = strtok (NULL, " \n\0");
		}
		argumentos[k] = '\0';
		int p = fork();
		if(p==0){
			execvp(argumentos[0], argumentos);
		} else {
			int status;
			wait(&status);
		}
	}
}
//5