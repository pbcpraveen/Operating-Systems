#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main()
{
  char s[50];
  printf("Enter: ");
  scanf("%s",s);
  char *t= strtok(s,"/");
  while(t!=NULL)
    {
      printf("%s\n",t);
      t=strtok(NULL,"/");
    }
  printf("Exit\n");
}
