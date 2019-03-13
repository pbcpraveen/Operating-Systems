#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct files {
    char fname[10];
}File;
typedef struct directory {
    char fname[10];
    int c;
    File* l[5];
}Directory;
typedef struct unit {
    int d;
    void *p;
}Unit;
Unit root[50];
int count = 0;
File* new_file(char s[])
{
    File* n = (File*)malloc(sizeof(File));
    strcpy(n->fname, s);
    return n;
}
Directory* new_dir(char s[])
{
    Directory* n = (Directory*)malloc(sizeof(Directory));
    strcpy(n->fname, s);
    n->c = 0;
    for(int i = 0; i < 5; i++) n->l[i] = NULL;
    return n;
}
int search_file(char s[])
{
    int flag = 0;
    for(int i = 0; i < count; i++)
    {
        if(root[i].p != NULL) {
            if(strcmp(((File*)(root[i].p))->fname,s) == 0 && root[i].d == 0) {
                flag = 1;
                break;
            }
        }
    }
    return flag;
}
Directory* search_dir(char s[])
{
    Directory* flag = NULL;
    for(int i = 0; i < count; i++)
    {
        if(root[i].p != NULL) {
            if(strcmp(((Directory*)(root[i].p))->fname,s) == 0 && root[i].d == 1) {
                flag = ((Directory*)(root[i].p));
                break;
            }
        }
    }
    return flag;
}
void insert_file(char s[])
{
    if(count >= 50) {
        printf("Full!\n");
        return;
    }
    if(search_file(s) == 1) {
        printf("File %s already exists!\n", s);
        return;
    }
    if(search_dir(s) != NULL) {
        printf("Directory named %s already exists!\n", s);
        return;
    }
    root[count].p = new_file(s);
    root[count].d = 0;
    count++;
    printf("Created!\n");
}
void insert_file_dir(Directory* d, char s[])
{
    int i, pos;
    if(d->c >= 5) {
        printf("Directory full!\n");
        return;
    }
    for(i = 0; i < 5; i++)
    {
        if(d->l[i] != NULL) {
            if(strcmp(d->l[i]->fname, s)==0) {
                printf("File already exists!\n");
                return;
            }
        }
        else {
            pos = i;
            i = 5;
        }
    }
    d->l[pos] = new_file(s);
    d->c = d->c + 1;
    printf("Created!\n");
}
void insert_dir(char s[])
{
    if(count >= 50) {
        printf("Full!\n");
        return;
    }
    if(search_dir(s) != NULL) {
        printf("Directory %s already exists!\n", s);
        return;
    }
    if(search_file(s) == 1) {
        printf("File named %s already exists!\n", s);
        return;
    }
    root[count].p = new_dir(s);
    root[count].d = 1;
    count++;
    printf("Created!\n");
}
void display(Unit d[])
{
    printf("Contents of root:\n");
    if(count == 0) {
        printf("Empty!\n");
        return;
    }
    int ch = 0;
    printf("Files:\n");
    for(int i = 0; i < count; i++) {
        if(root[i].p != NULL) {
            if(root[i].d == 0) {
                printf("%s ",((File*)(root[i].p))->fname); ch++;
            }
        }
    }
    if(ch == 0) printf("None!");
    printf("\nDirectories:\n");
    ch = 0;
    int dc = 0;
    for(int i = 0; i < count; i++) {
        if(root[i].p != NULL) {
            if(root[i].d == 1) {
                ch++;
                printf("%s ",((Directory*)(root[i].p))->fname);
            }
        }
    }
    if(ch == 0) printf("None!");
    printf("\n");
    ch = 0;
    for(int i = 0; i < count; i++) {
        if(root[i].p != NULL) {
            if(root[i].d == 1) {
                ch++;
                printf("Contents of %s:\n",((Directory*)(root[i].p))->fname);
                dc = 0;
                for(int j = 0; j < 5; j++)
                    if(((Directory*)(root[i].p))->l[j] != NULL) {
                        printf("%s ", ((Directory*)(root[i].p))->l[j]->fname);
                        dc++;
                    }
                if(dc == 0) printf("None!");
                printf("\n");
            }
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
        printf("2. New Directory\n");
        printf("3. Display all files\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&c);
        if(c==1)
        {
            char d[10], s[10];
            printf("Enter root to create file in the root directory.\nEnter root/directory to create file in the sub-directory.\nEnter directory: ");
            scanf("%s",d);
            printf("Enter file name: ");
            scanf("%s", s);
            if(strcmp(d,"root")!=0)
            {
                char* n = strtok(d, "/");
                n = strtok(NULL, "/");
                Directory* dir = search_dir(n);
                if(dir != NULL) {
                    insert_file_dir(dir, s);
                }
                else printf("No such directory!\n");
            }
            else if(strcmp(d,"root")==0) {
                insert_file(s);
            }
        }
        else if(c==2)
        {
            char d[10];
            printf("Enter directory name: ");
            scanf("%s", d);
            insert_dir(d);
        }
        else if(c==3)
        {
            display(root);
        }
        else
        {
            break;
        }
    }
}


