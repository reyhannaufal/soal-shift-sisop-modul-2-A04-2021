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

void make();
void placeholdir(time_t time);
void download (char *tang,int par);
void caesar5(char *succ);
void zipfolder(char *tang);

void _fork_(char *cmd, char *arg[])
{
	pid_t id;
	int status;
//	printf("\n===Test #1===\n");
	id = fork();
//	printf("\n===Test #2===\n");
	if(id<0)
	{
		exit(EXIT_FAILURE);
//		printf("booreal\n");
	}
	if(id==0)
	{
//		printf("fooreal\n");
		execv(cmd,arg);
		printf("kalo ketulis aneh");
	}
	else{
		while(wait(&status)>0){
		}
	}
}

void fork_(char *cmd, char *arg[])
{
	pid_t id;
	int status;
//	printf("\n===Test #1===\n");
	id = fork();
//	printf("\n===Test #2===\n");
	if(id<0)
	{
		exit(EXIT_FAILURE);
//		printf("booreal\n");
	}
	if(id==0)
	{
//		printf("fooreal\n");
		execv(cmd,arg);
		printf("kalo ketulis aneh");
	}
//	else{
//		while(wait(&status)>0){
//		}
//	}
}


void caesar5(char* succ){
	int i;
	for(i=0;i<(sizeof(succ));i++){
		if (((succ[i] >= 'a') && (succ[i]<= 'z'-5))||((succ[i] >= 'A')&&(succ[i]<= 'z'-5))){
			succ[i] =succ[i] + 5;
		}
		else if (((succ[i] <= 'z') && (succ[i] > 'z'-5))||((succ[i] <= 'Z')&&(succ[i]> 'z'-5))){
			succ[i] = succ[i] - 21;
		}
	}
}


void createdir(char *date){
	char *arg1[] = {"cp", "-r" ,"/home/san/Downloads",date,NULL};
	fork_("/bin/cp", arg1);
}


void download (char *tang, int par){
	
	time_t waktu;
	time(&waktu);
	char* date;
	char* pix;
	char* date2;
	struct tm tim = *localtime(&waktu);
	asprintf(&pix,"https://picsum.photos/%li" ,waktu%1000+50);
	asprintf(&date,"%d-%02d-%02d_%02d:%02d:%02d" , tim.tm_year +1900, tim.tm_mon +1, tim.tm_mday, tim.tm_hour, tim.tm_min, tim.tm_sec);
	asprintf(&date2,"%s/%s.jpeg", tang,date);
	char *arg[]={"wget","--no-check-certificate","-O",date2,pix,NULL};
	if(par == 0){
		fork_("/usr/bin/wget",arg);
	}
	if(par == 1){
		_fork_("usr/bin/wget",arg);
	}
}

void placeholdir(time_t waktu){
	char* date;
	struct tm tim = *localtime(&waktu);
	asprintf(&date,"%d-%02d-%02d_%02d:%02d:%02d" , tim.tm_year +1900, tim.tm_mon +1, tim.tm_mday, tim.tm_hour, tim.tm_min, tim.tm_sec);
	char *arg[]={"mkdir",date,NULL};
	fork_("/bin/mkdir",arg);
	int i;
	for(i=0;i<10;i++){
	sleep(2);
	download(date,0);
	}
	sleep(5);
	zipfolder(date);
	
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

void zipfolder(char *tang){
	char* zipname;
	asprintf(&zipname,"%s.zip",tang);
	char* arg[] = {"zip","-r",zipname,tang,NULL};
	fork_("/usr/bin/zip",arg);
}

int main(int argc, char *argv[])
{
	printf("helloworld\n");
	make();
	printf("make1\n");
	sleep(1);
	make();
	printf("make2\n");

	return 0;
}



