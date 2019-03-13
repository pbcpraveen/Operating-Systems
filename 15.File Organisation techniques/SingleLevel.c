#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct files {
    char fname[10];
}File;
File* root[50];
int fcount = 0;
File* new_file(char s[])
{
    File* n = (File*)malloc(sizeof(File));
    strcpy(n->fname, s);
    return n;
}
int search_file(char s[])
{
    int flag = 0;
    for(int i = 0; i < fcount; i++)
    {
        if(root[i] != NULL) {
            if(strcmp(root[i]->fname,s) == 0) {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}
void insert_file(char s[])
{
    if(search_file(s) == 1) {
        printf("File %s already exists!\n", s);
        return;
    }
    root[fcount] = new_file(s);
    fcount++;
    printf("Created!\n");
}
void display(File* d[])
{
    printf("Contents of root:\n");
    if(fcount == 0) {
        printf("Empty!\n");
        return;
    }
    for(int i = 0; i < fcount; i++) {
        if(root[i] != NULL) {
            printf("%s\t", root[i]->fname);
        }
    }
    printf("\n");
}
int main()
{
    int c;
    while(1)
    {
        printf("1. New File\n");
        printf("2. Display all files\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&c);
        if(c==1)
        {
            char s[50];
            printf("Enter file name: ");
            scanf("%s",s);
            insert_file(s);
        }
        else if(c==2)
        {
            display(root);
        }
        else {
            break;
        }
    }
}

