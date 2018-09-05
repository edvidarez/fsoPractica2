#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define NPROCS 3

void proc();
int shouldShutdown();
void createChild(int n,int level);
int k= 0;
int pids[NPROCS];

void createChild(int n,int level){

	if(n==level)
		return;
	int p = fork();
	if(p==0){
		proc();
	} else {

		pids[level] = p;
		createChild(n,level+1);
		int status;
		wait(&status);
		//printf("Status es: %d\t\t y el pid del hijo que termino es: %d\n",status>>8,getpid());
		if(shouldShutdown()){
			//printf("shouldShutdown\n");
			exit(0);
		}
		createChild(level+1,level);
	}
}
int shouldShutdown(){
	   FILE* file = fopen("shutdown.txt", "r");
	   char line[256];
	   while (fgets(line, sizeof(line), file)) {
	   	if(strcmp(line,"shutdown\n")==0){
	   		int i;
	   		for(i=0;i<NPROCS;i++){
	   			kill(pids[i], SIGINT);
	   		}
	   		return 1;
	   	}
	   }
	   return 0;
}
int resetShutdownFile(){
	FILE* file = fopen("shutdown.txt", "w");
	fprintf(file, "\n");
}

int main(){

	resetShutdownFile();
	createChild(NPROCS,0);
}

void proc()
{	
	//printf("iniciado pid: %d\n",getpid() );
	execlp("xterm", "xterm", "-e","./getty", NULL);

}











