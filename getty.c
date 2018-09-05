#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>


int login(char *userpass){
	FILE* file = fopen("users.txt", "r");
	char line[256];
	while (fgets(line, sizeof(line), file)) {
	   	if(strcmp(line,userpass)==0||strcmp(line,userpass+'\n')==0){
	   		return 1;
	   	}
	}
	return 0;
}
void requestData(){
	char user[100],pass[100];
	//execlp("clear", "clear",NULL);
	printf("Welcome to Getty.c \nUser:");
	scanf("%s",user);
	fflush(stdin);
	printf("Password:");
	scanf("%s",pass);
	char userpass[200] = "";
	strcat(userpass,user);
	strcat(userpass,":");
	strcat(userpass,pass);


	if(login(userpass)){
		int p;
		p = fork();
		if(p==0){
			execlp("./sh", "./sh",NULL);
		} else { 
			int status;
			wait(&status);
			status>>=8;
			if(status==1)
				exit(1);
			//printf("status: %d\n",status);
		}
	}
}
int main(){
	while(1){
		requestData();
	}
	
}