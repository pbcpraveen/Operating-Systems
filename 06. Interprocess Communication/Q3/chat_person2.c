#include<sys/ipc.h>
#define NULL 0
#include<sys/shm.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
  int id;
  char *a;
  char temp[50],t1[50];
  char s[50];
  strcpy(s,"*");
  id = shmget(115, 50, IPC_CREAT | 00666);
  a = shmat(id, NULL, 0);
  printf("You: ");
  scanf("%s",temp);
  strcat(s,temp);
  strcpy(a,s);
  strcpy(s,"*");
  while(1) {
    while(a[0]=='*');
    strcpy(t1,a);
     char *t = strtok(t1,"#");
    printf("Friend: %s\n",t);
    if(strcmp(t,"bye")==0)
      {
	strcpy(temp,"bye");
	printf("You: %s ",temp);
        sleep(5);
	break;
      }
    printf("You: ");
    scanf("%s",temp);
    strcat(s,temp);
    strcpy(a,s);
    strcpy(s,"*");
    if(strcmp(temp,"bye")==0)
      {
        sleep(5);
	break;
      }
  }
  printf("Connection Ended!\n");
  shmdt(a);
}
