
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
# include<unistd.h>
# include<stdio.h>
# include<stdlib.h>
# include<string.h>
#include <sys/wait.h>
#include <stdio_ext.h>
int main()
{
  printf("CLIENT-PROGRAM\n");
  int pid;
  char *a;
  int id,n,i;
  id=shmget(111,50,00666);
   a=shmat(id,0,0);
   sleep(10);
   for(int i = 0; a[i] != '\0'; i++)
		a[i] -= (a[i] >= 'a' && a[i] <= 'z') ? 32 : 0;
   printf("The uppercase version the message received is : %s\n",a);
   shmdt(a);
   shmctl(id, IPC_RMID,NULL);
   sleep(4);
}
