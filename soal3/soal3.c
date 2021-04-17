#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <syslog.h>
#include <errno.h>

void make();
void placeholdir(time_t time);
void download (char *tang);
void caesar5(char *succ);
void zipfolder(char *tang);
void text(char* path);
void removefolder(char *tang);

void fork_(char *cmd, char *arg[])
{
	pid_t id;
	int status;
	id = fork();
	if(id<0)
	{
		exit(EXIT_FAILURE);
	}
	if(id==0)
	{
		execv(cmd,arg);
	}
}



void caesar5(char* succ){
	int i=0;
	while (succ[i] != NULL){
		if (((succ[i] >= 'a') && (succ[i]<= 'z'-5))||((succ[i] >= 'A')&&(succ[i]<= 'z'-5))){
			succ[i] =succ[i] + 5;
		}
		else if (((succ[i] <= 'z') && (succ[i] > 'z'-5))||((succ[i] <= 'Z')&&(succ[i]> 'z'-5))){
			succ[i] = succ[i] - 21;
		}
		i++;
	}
}


void download (char *tang){
	printf("\nFOOBAR1\n");
	time_t waktu;
	time(&waktu);
	char* date;
	char* pix;
	char* date2;
	struct tm tim = *localtime(&waktu);
	asprintf(&pix,"https://picsum.photos/%li" ,waktu%1000+50);
	asprintf(&date,"%d-%02d-%02d_%02d:%02d:%02d" , tim.tm_year +1900, tim.tm_mon +1, tim.tm_mday, tim.tm_hour, tim.tm_min, tim.tm_sec);
	asprintf(&date2,"%s/%s.jpeg", tang,date);
	char *arg[]={"wget","--no-check-certificate","-O",date2,"-b","-q","-c",pix,NULL};
	fork_("/usr/bin/wget",arg);
}

void placeholdir(time_t waktu){
	char* date;
	struct tm tim = *localtime(&waktu);
	asprintf(&date,"%d-%02d-%02d_%02d:%02d:%02d" , tim.tm_year +1900, tim.tm_mon +1, tim.tm_mday, tim.tm_hour, tim.tm_min, tim.tm_sec);
	char *arg[]={"mkdir",date,NULL};
	fork_("/bin/mkdir",arg);
	int i;
	for(i=0;i<10;i++){
	download(date);
	sleep(5);
	}
	text(date);
	zipfolder(date);
	sleep(5);
	removefolder(date);
	
}


void make(){
	time_t waktu;
	time(&waktu);
	pid_t id;
	int status;
	id =fork();
	if (id<0){
		exit(EXIT_FAILURE);
	}
	if (id==0){
		placeholdir(waktu);
		char* sk[]={"echo","-n",NULL};
		execv("/bin/echo", sk);
	}

}

void text(char* path){

	FILE *tex;
	char *namafile;
	asprintf(&namafile,"%s/status.txt",path);
	char* msg;
	asprintf(&msg,"Download Success");
	tex = fopen(namafile, "w");
	caesar5(msg);
	fputs(msg,tex);
	fclose(tex);
}



void zipfolder(char *tang){
	char* zipname;
	asprintf(&zipname,"%s.zip",tang);
	char* arg[] = {"zip","-r",zipname,tang,NULL};
	fork_("/usr/bin/zip",arg);
	
}

void removefolder(char *tang){
	char* arg[]={"rm","-rf",tang,NULL};
	fork_("/bin/rm",arg);
}

void killer(char *c,int pid,char* ch){
	FILE *tex;
	char* script;
	tex = fopen("Killer.sh", "w");
	if((c=='x') || (c =='X')){
		asprintf(&script,"\#!/bin/bash\nkill -9 %d\nrm -- \"$0\"",pid);
		fputs(script,tex);
		fclose(tex);
	}
	if((c=='z') || (c =='Z')){
		asprintf(&script,"\#!/bin/bash\nkillall -9 %s\nrm -- \"$0\"",ch);
		fputs(script,tex);
		fclose(tex);
	}
}



int main(int argc,char* argv[])
{
	if(argc !=2){
		printf("invalid # arg\n");
		exit(0);
	}
	if(!((argv[1][1]=='x')||(argv[1][1]=='X')||(argv[1][1]=='z')||(argv[1][1]=='Z'))){
		printf("\ninvalid arg = %c\n",argv[1][1]);
		exit(0);
	
	}
	char s[PATH_MAX];
	getcwd(s,sizeof(s));
	
	pid_t pid,sid;
	pid = fork();
	
	if(pid <0){
		exit(EXIT_FAILURE);
	}
	if(pid > 0){
		exit(EXIT_SUCCESS);
	}
	umask(0);
	sid = setsid();
	if(sid < 0){
		exit(EXIT_FAILURE);
	}
	if((chdir(s))<0){
		printf("\nbar\n");
		exit(EXIT_FAILURE);
	}
	
	killer(argv[1][1],(int)getpid(),argv[0]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	while(1){
		printf("foo");
		make();
		sleep(40);
	}
	return 0;
}



