#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Page{
  char process[10];
  int is_free;
  int page_no;
  struct Page *next;
  
};
struct Process
{
  char pname[10];
  struct Process *next;
};
typedef struct Process process;
process *pro = NULL;

typedef struct Page page;

page *memory=NULL;
page *freelist=NULL;
int num_free_frames=0;
page* insert(page *p , int frame)
{
  page* temp = p;
  page* i= (page*) malloc(sizeof(page));
  strcpy(i->process," ");
  i->is_free=1;
  i->page_no=frame;
  i->next=NULL;
  if(temp==NULL)
    p=i;
  else{
  while(temp->next!=NULL) temp=temp->next;
  temp->next=i;
  }
  num_free_frames++;
  return p;
}

page* delete(page *head)
{
  if(head!=NULL)
    {
      page *temp = head;
      head=head->next;
      free(temp);
      num_free_frames--;
    }
  return head;
}

int is_frame_free(int j)
{
  page *temp=memory;
  while(temp!=NULL&&temp->page_no!=j) temp=temp->next;
  if(temp->is_free==1)
    return 1;
  else
    return 0;
}

page* allocate(page *head,char name[],int frame)
{
  page *temp = head;
  if(head!=NULL&&head->page_no==frame)
    {
       strcpy(head->process,name);
       head->is_free=0;
    }
  else{
  while(temp!=NULL&&temp->page_no!=frame)
    {
      
      temp=temp->next;
    }
  strcpy(temp->process,name);
  temp->is_free=0;
  }
  return head;
}

page* deallocate(page *head,int frame)
{
  page *temp;
  while(temp!=NULL&&temp->page_no!=frame)
    {
      temp=temp->next;
    }
  strcpy(temp->process," ");
  temp->is_free=1;
  freelist=insert(freelist,frame);
  return head;
}

void main()
{
  page *temp;
  int mem_size,page_size;
  printf("Enter the memory size:");
  scanf("%d",&mem_size);
  printf("Enter the page size:");
  scanf("%d",&page_size);
  int n=mem_size/page_size;
  int f=0;
  //initialising all the lists.
  for(int i=0;i<n;i++)
    {
      memory=insert(memory,i); 
    }
  //creating the initial state by assing memory randomly;
  for(int i=0;i<n/2;i++)
  {
    int j=rand()%n;
    if(is_frame_free(j))
      {
	memory=allocate(memory,"random ",j);
      }
    else i--;
  }
  //finding the free pages
  temp=memory;
  while(temp!=NULL)
    {
      if(temp->is_free==1)
	{
	  freelist=insert(freelist,temp->page_no);
	}
      temp=temp->next;
    }
  int ch=1;
  int ch2;
  while(ch)
    {
      printf("1. Process Request\n");
      printf("2. Deallocate\n");
      printf("3. Page table display for all input process\n");
      printf("4. free frame list\n");
      printf("5. Exit\n");
      printf("Enter your choice: ");
      scanf("%d",&ch2);
      if(ch2==1)
	{
	  char pname[10];
	  int size;
	  printf("Enter the process ID: ");
	  scanf("%s",pname);
	  printf("Enter the process size: ");
	  scanf("%d",&size);
	  int reqpage=size/page_size;
	  if(size%page_size!=0)
	    reqpage++;
	  int g=0;
	  if(num_free_frames>=reqpage)
	    {
	      process *ptemp = (process*)malloc(sizeof(process));
	      strcpy(ptemp->pname,pname);
	      ptemp->next=NULL;
	      if(pro==NULL)
		pro=ptemp;
	      else
		{
		  ptemp->next=pro;
		  pro=ptemp;
		}
	      while(g<reqpage)
		{
		  int d=freelist->page_no;
		  freelist=delete(freelist);
		  memory = allocate(memory,pname,d);
		  g++;
		}
	    }
	  else
	    printf("NOT ENOUGH FRAMES AVAILABLE");
	}
      else if(ch2==2)
	{
	  char dname[10];
	  printf("Enter the process ID that you want to deallocate: ");
	  scanf("%s",dname);
	  temp=memory;
	  process *temp2 = pro;
	  if(strcpy(pro->pname,dname)==0)
	    {
	      pro=pro->next;
	      free(temp2);
	    }
	  else
	    {
	      while(temp2!=NULL&&strcpy(temp2->next->pname,dname)==0)
		temp2=temp2->next;
	      process *t1=temp2->next;
	      temp2->next=t1->next;
	      free(t1);
	    }
	  while(temp!=NULL)
	    {
	      if(strcpy(temp->process,dname)==0)
		{
		  memory =deallocate(memory,temp->page_no);
		}
	    }
	  
	}
      else if(ch2==3)
	{
	  process *t = pro;
	  while(t!=NULL)
	    {
	      temp=memory;
	      printf("%s :",t->pname);
	      while(temp!=NULL)
		{
		  if(strcpy(temp->process,t->pname)==0)
		    printf("%d ",temp->page_no);
		  temp=temp->next;
		}
	       printf("\n");
	       t=t->next;
	    }
	 
	}
      else if(ch2==4)
	{
	  temp=freelist;
	  while(temp!=NULL)
	    {
	      printf("%d ",temp->page_no);
	      temp=temp->next;
	    }
	  printf("\n");
	}
      else if(ch2==5)
	{
	  ch=0;
	}
    }
  
  
  
}
