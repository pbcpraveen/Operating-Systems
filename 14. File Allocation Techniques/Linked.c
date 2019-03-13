#include<stdio.h>
#include<stdlib.h>
typedef struct list {
    int block;
    struct list *next;
}List;
typedef struct file {
    char n[10];
    int s, b;
    List* head;
}File;
File files[100];
int freeb[100], mem, bsize, n, nf, c, r, f;
List* newnode(int n)
{
    List* p = (List*)malloc(sizeof(List));
    p->block = n;
    p->next = NULL;
    return p;
}
void print(List* head)
{
    for(List* t = head; t != NULL; t = t->next)
    {
        printf("%d",t->block);
        if(t->next == NULL) printf("\n");
        else printf("->");
    }
}
int main()
{
    printf("Enter size of memory in KB: ");
    scanf("%d", &mem);
    printf("Enter size of block in KB: ");
    scanf("%d", &bsize);
    printf("No. of blocks = %d\n", mem/bsize);
    n = mem/bsize;
    nf = n;
    for(int i = 0; i <= n/3; i++) {
        r = random()%n;
        if(freeb[r] == 1) {
            i--;
        }
        else {
            freeb[r] = 1;
            nf--;
        }
    }
    printf("Free blocks:\n");
    for(int i = 0; i < n; i++) {
        if(freeb[i] == 0) printf("%d ", i);
    }
    printf("\nEnter no. of files: ");
    scanf("%d", &f);
    for(int i = 0; i < f; i++) {
        printf("Enter name of file %d: ", i+1);
        scanf("%s", (files[c].n));
        printf("Enter size in KB: ");
        scanf("%d", &files[c].s);
        files[c].b = files[c].s/bsize;
        if(files[c].s*1.0/bsize > files[c].b) (files[c].b)++;
        if(files[c].b > nf) {
            printf("Can't allocate!\n");
            i--;
        }
        else {
            List *t, *p;
            for(int j = 0; j < files[c].b; j++) {
                r = random()%n;
                if(freeb[r] == 0) {
                    freeb[r] = 1;
                    nf--;
                    t = newnode(r);
                    if(j == 0) {
                        files[c].head = t;
                        p = files[c].head;
                    }
                    else {
                        p->next = t;
                        p = t;
                    }
                }
                else j--;
            }
            c++;
        }
        if(nf == 0) {
            printf("Memory over!\n");
            f = c;
            break;
        }
    }
    printf("\nFile allocation:\n");
    for(int i = 0; i < f; i++) {
        printf("File %s:\n",files[i].n);
        print(files[i].head);
        printf("\n");
    }
    return 0;
}
