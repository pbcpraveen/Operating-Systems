#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct memory {
  int block;
  int isfree;
  char f[50];
};
typedef struct memory memory;
memory disc[100];
int blocksize=4;
void initialise()
{
  for(int i=0;i<100;i++)
    {
      disc[i].block=i;
      disc[i].isfree=1;
      strcpy(disc[i].f,"---");
    }
}

struct element{
  int block;
  int size;
  char f[50];,
  struct element *next;
};
typedef struct element element;
element *table=NULL;
void insertfile(char f[],int size,int block)
{
  element *newnode = (element*)malloc(sizeof(element));
  newnode->next=NULL;
  newnode->block = block;
  newnode->size = size;
  strcpy(newnode->f,f);
  if (table == NULL)
    table = newnode;
  else
    {
      newnode->next = table;
      table = newnode;
    }
}

void display()
{
  element *temp = table;
  printf("FILE\tBLOCK\tSIZE\n");
  while(temp!=NULL)
    {
      printf("%s\t%d\t%d\n",temp->f,temp->block,temp->size);
      temp=temp->next;
    }
}
int checkfree(int size)
{
  int ind=-1;
  int reqblocks=size/blocksize;
  if(size/(float)blocksize-reqblocks > 0)
    reqblocks++;
  for(int i=0;i<100;)
    {
      if(disc[i].isfree==1)
	{
	  int flag=0;
	  int j=i;
	  while(disc[j].isfree==1&&j<nb)
	    {
	      if(j-i+1==reqblocks)
		{
		  return i;
		}
	      j++;
	    }
	  i+=(j+1);
	}
      else
	i++;
    }
  return ind;
}

int check(int ind,int size)
{
  if(disc[ind].isfree)
    {
      for(int i=ind;i<ind+size;i++)
        {
	  if(!disc[i].isfree)
	    return 0;
	}
    }
  return 1;
}

int  allocate(int size,char name[])
{
  int flag =0;
  if(checkfree(size)>=0)
    {
      
      while(1)
	{int possible[100];
	  int np=0;
	  int ind = rand()%100;
	  if(check(ind,size)){
	    
	    flag=1;
	    int b= size/blocksize;
	    if(size/(float)blocksize-b>0)
	      b++;
	    for (int i=ind;i<=b+ind;i++)
	      {
		disc[i].isfree=0;
		strcpy(disc[i].f,name);
	      }
	    insertfile(name,b,ind);
	    break;
	  }
	}

    }
  else
    printf("Memeory not available for the file!!!!!!! \n");
  
  return flag==0?0:1;
}



int main()
{
  initialise();
  int ch;
  char f[50];
  int size;
  int block;
  while(1)
    {
      printf("1.Allocate\n2.Display\n3.Exit\nEnter your choice: ");
      scanf("%d",&ch);
      if(ch==1)
	{
	  printf("Enter the file name: ");
	  scanf("%s",f);
	  printf("Enter the size of the file: ");
	  scanf("%d",&size);
	  allocate(size,f);
	  
	}
      else if(ch==2)
	{
	  display();
	}
      else
	break;
    }
}
