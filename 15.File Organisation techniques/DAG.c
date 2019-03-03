#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Files {
  char fname[10];
};
typedef struct Files file;
struct Directory {
  char dname[10];
  struct Directory *d1,*d2,*d3;
  file *f1,*f2;
};
typedef struct Directory directory;

directory *root=NULL;

void insert_directory(char s[])
{
  directory* temp=root;
  char *t=strtok(s,"/");
  t=strtok(NULL,"/");
  while(t!=NULL){
    if(temp->d1!=NULL&&strcmp(t,temp->d1->dname)==0)
      {
	temp=temp->d1;
      }
    else if(temp->d2!=NULL&&strcmp(t,temp->d2->dname)==0)
      {
	temp=temp->d2;
      }
    else if(temp->d3!=NULL&&strcmp(t,temp->d3->dname)==0)
      {
	temp=temp->d3;
      }
    t= strtok(NULL,"/");
  }
    if(t==NULL)
      {
	if(temp->d1==NULL||temp->d2==NULL||temp->d3==NULL)
	  {
	    char d[10];
	    printf("Enter the directory name: ");
	    scanf("%s",d);
	    directory* newdir = (directory*)malloc(sizeof(directory));
	    strcpy(newdir->dname,d);
	    if(temp->d1==NULL)
	      {
		temp->d1=newdir;
	      }
	    else if(temp->d2==NULL&& strcmp(d,temp->d1->dname)!=0)
	      {
		temp->d2=newdir;
	      }
	    else if( strcmp(d,temp->d1->dname)!=0&& strcmp(d,temp->d2->dname)!=0)
	      {
		temp->d3=newdir;
	      }
	    else if( strcmp(d,temp->d1->dname)==0|| strcmp(d,temp->d2->dname)==0)
	      printf("Duplicate directories not allowed: Invalid Entry\n");
	    
	    }
	else  
	  printf("Directory limit Exceeded\n");
      }// close of if(t==NULL)
    
}//close of function

void insert_file(char s[])
{
  directory* temp=root;
  char temp1[100];
  strcpy(temp1,s);  
  char *t=strtok(s,"/");
  t=strtok(NULL,"/");
  while(t!=NULL){
    if(temp->d1!=NULL&&strcmp(t,temp->d1->dname)==0)
      {
	temp=temp->d1;
      }
    else if(temp->d2!=NULL&&strcmp(t,temp->d2->dname)==0)
      {
	temp=temp->d2;
      }
    else if(temp->d3!=NULL&&strcmp(t,temp->d3->dname)==0)
      {
	temp=temp->d3;
      }
    t= strtok(NULL,"/");
  }
    if(t==NULL)
      {
	if(temp->f1==NULL||temp->f2==NULL)
	  {
	    char d[10];
	    printf("Enter the file name: ");
	    scanf("%s",d);
	    file *newfile = (file*)malloc(sizeof(file));
	    strcpy(newfile->fname,d);
	    if(temp->f1==NULL)
	      {
		temp->f1=newfile;
	      }
	    else if(temp->f2==NULL)
	      {
		temp->f2=newfile;
	      }
	  }
	else
	  printf("Directory file limit Exceeded");
      }// close of if(t==NULL)
    
}//close of function

file* get_file_pointer(char s[])
{
  char *t= strtok(s,"/");
  char *g;
  directory *temp=root;
  while(t!=NULL){
    if(temp->d1!=NULL&&strcmp(t,temp->d1->dname)==0)           //
      {                                        //
	temp=temp->d1;                          //
      }                                         //
    else if(temp->d2!=NULL&&strcmp(t,temp->d2->dname)==0)      //    if "file" name part of the string is reached then all the if an else id would fail 
      {                                        //    
	temp=temp->d2;                          //
      }                                        //
    else if(temp->d3!=NULL&&strcmp(t,temp->d3->dname)==0)      //
      {
	temp=temp->d3;
      }
    g=t;//g will store the last parsed part of the string . This will the the file name.
    t= strtok(NULL,"/");
    if(t==NULL)
      {
	if(strcmp(temp->f1->fname,g)==0)
	  return temp->f1;
	else if(strcmp(temp->f2->fname,g)==0)
	  return temp->f2;
	else
	  {
	    printf("ERROR: NO SUCH FILE FOUND\n");
	    return NULL;
	  }
      }//close of if(t==NULL)
  }//close of while
}// close of function.





directory* get_directory_pointer(char s[])
{
  char *t= strtok(s,"/");
  char *g;
  directory *temp=root;
  while(t!=NULL){
    if(temp->d1!=NULL&&strcmp(t,temp->d1->dname)==0)           //
      {                                        //
	temp=temp->d1;                          //
      }                                         //
    else if(temp->d2!=NULL&&strcmp(t,temp->d2->dname)==0)      //   
      {                                        //    
	temp=temp->d2;                          //
      }                                        //
    else if(temp->d3!=NULL&&strcmp(t,temp->d3->dname)==0)      //
      {
	temp=temp->d3;
      }
    g=t;
    t= strtok(NULL,"/");
    if(t==NULL)
      {
	return temp;
      }//close of if(t==NULL)
  }//close of while
}// close of function.

void create_link(char s1[],char s2[])
{
  file* f1= get_file_pointer(s1);
  char a[300];
  directory* d2=get_directory_pointer(s2);
  if(f1!=NULL){
    if(d2->f1==NULL)
      {
	d2->f1=f1;
      }
    else if(d2->f2==NULL)
      {
	d2->f2=f1;
	
      }
    else
      {
	printf("Not enough space in the directory to make the link.\n");
      }
  }
}
void display_file(file* f,char s[])
{
  printf("%s\t\t%s\n",f->fname,s);
}

void display(directory* r,char s[])   // this is a simple n-ary tree traversal routine
{
  if(r!=NULL)
    {
      strcat(s,r->dname);
      strcat(s,"/");
      if(r->f1!=NULL)
	{
	  display_file(r->f1,s);
	}
      if(r->f2!=NULL)
	{
	  display_file(r->f2,s);
	}
      display(r->d1,s);
      display(r->d2,s);
      display(r->d3,s);
    }
}

int main()
{
  root= (directory* )malloc(sizeof(directory));
  strcpy(root->dname,"root");
  root->d1=NULL;
  root->d2=NULL;
  root->d3=NULL;
  root->f1=NULL;
  root->f2=NULL;
  int c;
  while(1)
    {
      printf("1. Insert a Directory.\n");
      printf("2. Insert a File.\n");
      printf("3. Create another link to the file.\n");
      printf("4. Display all the file.\n");
      printf("5. Exit.\n");
      printf("Enter your choice: ");
      scanf("%d",&c);
      if(c==1)
	{
	  printf("==============================================\n");
	  printf("   Insert a Directory to the Tree.           \n");
	  printf("==============================================\n");
	  char s[50];
	  printf("Path format:- \n");
	  printf("root/ (or) root --------> to insert a directory in root\n");
	  printf("root/directory1/------> to insert into the directory1 in root\n");
	  printf("Note: You need to create the directory1 before you do operation on it.\n\n");
	  printf("Enter the path: ");
	  scanf("%s",s);
	  insert_directory(s);
	}
      else if(c==2)
	{
	  printf("==============================================\n");
	  printf("   Insert a File to the Tree.           \n");
	  printf("==============================================\n");
	  char s[50];
	  printf("Path format:- \n");
	  printf("root/ (or) root --------> to insert a file in root\n");
	  printf("root/directory1/------> to insert file into the directory1 in root\n");
	  printf("Note: You need to create the directory1 before you do operation on it.\n\n");
	  printf("Enter the path: ");
	  scanf("%s",s);
	  insert_file(s);
	}
      else if(c==3)
	{
	  printf("==============================================\n");
	  printf("  Create another link to the File              \n");
	  printf("==============================================\n");
	  char s1[50];
	  char s2[50];
	  printf("Enter the complete path of the file(including the file name): ");
	  scanf("%s",s1);
	  printf("Enter the path of the directory with which you want to create link: ");
	  scanf("%s",s2);
	  create_link(s1,s2);
	  
	}
      else if(c==4)
	{
	  char s[400];
	  strcpy(s,"/");
	  printf("FILE\t\tPATH\n");
	  display(root,s);
	}
      else{
	break;
      } 
    }
  
}
