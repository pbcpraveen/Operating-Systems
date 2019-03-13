#include<stdio.h>
#include<stdlib.h>
typedef struct file {
    char n[10];
    int s, b;
    int i;
}File;
typedef struct indexblock {
    int blockid;
    int blocks[100];
} IndexBlock;
IndexBlock index1[100];
File files[100];
int freeb[100], mem, bsize, n, nf, c, r, f;
void print(int i)
{
    printf("Index block no.: %d\nBlock table:\n", index1[i].blockid);
    for(int j = 0; j < files[i].b; j++) {
        printf("%d ", index1[i].blocks[j]);
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
        scanf("%s", files[c].n);
        printf("Enter size in KB: ");
        scanf("%d", &files[c].s);
        files[c].b = files[c].s/bsize;
        if(files[c].s*1.0/bsize > files[c].b) (files[c].b)++;
        if(files[c].b + 1 > nf) {
            printf("Can't allocate!\n");
            i--;
        }
        else {
            do {
                r = random()%n;
            }while(freeb[r] == 1);
            index1[c].blockid = r;
            files[c].i = r;
            freeb[r] = 1;
            nf--;
            for(int j = 0; j < files[c].b; j++) {
                r = random()%n;
                if(freeb[r] == 0) {
                    freeb[r] = 1;
                    nf--;
                    index1[c].blocks[j] = r;
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
    printf("\nFile Allocation:\n");
    for(int i = 0; i < f; i++) {
        printf("File %s:\n",files[i].n);
        print(i);
        printf("\n");
    }
    return 0;
}

