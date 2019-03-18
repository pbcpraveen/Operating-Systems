#include<stdio.h>
#include<stdlib.h>
int resource[5];
int allocated[5][5];
int need[5][5];
int max[5][5];
int available[5];
int total[5];
int safety[5];
int overp[5];
int M, N;
int talloc[5][5], tneed[5][5], tavail[5], diff[5];
int c = 0, no = 0, ncheck = 0, ch, dead = 0;
void read()
{
    
    c = 0; no = 0; ncheck = 0; dead = 0;
    printf("No. of resources and processes: ");
    scanf("%d %d", &M, &N);
    for(int j = 0; j < M; j++) {
        total[j] = 0;
        diff[j] = 0;
        tavail[j] = 0;
        available[j] = 0;
        overp[j] = 0;
        safety[j] = 0;
        resource[j] = 0;
        for(int i = 0; i < N; i++) {
            allocated[i][j] = 0;
            need[i][j] = 0;
            max[i][j] = 0;
            talloc[i][j] = 0;
            tneed[i][j] = 0;
        }
    }
    for(int i = 0; i < M; i++)
    {
        printf("Total no. of resource %d: ", i+1);
        scanf("%d", &resource[i]);
    }
    for(int i = 0; i < N; i++)
    {
        printf("Process %d:\nAllocated: ", i+1);
        for(int j = 0; j < M; j++) {
            scanf("%d", &allocated[i][j]);
            total[j] += allocated[i][j];
        }
        printf("Maximum: ");
        for(int j = 0; j < M; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }
    for(int i = 0; i < M; i++) {
        available[i] = resource[i] - total[i];
        if(available[i] < 0) {
            printf("Error! Re-enter data!\n");
            for(int j = 0; j < M; j++) available[j] = 0;
            break;
        }
    }
}
void print()
{
    printf("Data:\nP\tAlloc\t\t Max\t\t  Need\t\t   Available\n \t");
    for(int a = 0; a < 4; a++) {
        for(int b = 0; b < M; b++) {
            printf("R%d ",b+1);
        }
        if(a != 3) printf("\t");
        for(int s = 0; s <= a && a<=2; s++) printf(" ");
    }
    printf("\n \t     \t\t    \t\t      \t\t   ");
    for(int b = 0; b < M; b++) printf("%2d ",available[b]);
    printf("\n");
    for(int i = 0; i < N; i++)
    {
        printf("%d\t", i+1);
        for(int b = 0; b < M; b++) printf("%2d ",allocated[i][b]);
        printf("\t ");
        for(int b = 0; b < M; b++) printf("%2d ",max[i][b]);
        printf("\t  ");
        for(int b = 0; b < M; b++) printf("%2d ",need[i][b]);
        printf("\n");
    }
}
void bankers()
{
    dead = 0;
    for(int i = 0; i < M; i++) {
        tavail[i] = available[i];
    }
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            talloc[i][j] = allocated[i][j];
            tneed[i][j] = need[i][j];
        }
    }
    c = 0; no = 0;
    for(int i = 0; i < N; i++) overp[i] = 0;
    while(c < N) {
        no = 1;
        for(int i = 0; i < N; i++)
        {
            ncheck = 0;
            if(!overp[i]) {
                for(int j = 0; j < M; j++)
                {
                    diff[j] = tavail[j] - tneed[i][j];
                    if(diff[j] < 0) ncheck = 1;
                }
                if(ncheck != 1) {
                    for(int k = 0; k < M; k++) {
                        tavail[k] += talloc[i][k];
                    }
                    printf("P%d is over!\n", i+1);
                    overp[i] = 1;
                    safety[c] = i+1;
                    c++;
                    no = 0;
                }
            }
        }
        if(no == 1) {
            printf("\nDeadlock!\n");
            dead = 1;
            for(int k = 0; k < N; k++)
                if(overp[k] != 1) printf("P%d ",k+1);
            printf("\n");
            break;
        }
    }
    printf("\n");
    if(c == N)
    {
        printf("Safety: ");
        for(int i = 0; i < N; i++) printf("P%d ", safety[i]);
    }
    printf("\n");
}
void request()
{
    int p, r[10], can = 1;
    printf("Process: ");
    scanf("%d", &p);
    printf("Request for: ");
    for(int i = 0; i < M; i++) {
        scanf("%d", &r[i]);
    }
    for(int i = 0; i < M; i++) {
        if(available[i] - r[i] < 0) can = 0;
    }
    if(can == 0) printf("\nCannot request!\n");
    else {
        for(int i = 0; i < M; i++) {
            allocated[p-1][i] += r[i];
            need[p-1][i] -= r[i];
            available[i] -= r[i];
        }
        print();
        bankers();
        if(dead == 1) {
            for(int i = 0; i < M; i++) {
                allocated[p-1][i] -= r[i];
                need[p-1][i] += r[i];
                available[i] += r[i];
            }
        }
    }
}
void menu()
{
    printf("1. Enter data 2. Print data 3. View Sequence 4. Request 5. Exit\nChoice: ");
    scanf("%d", &ch);
    if(ch == 1) read();
    else if(ch == 2) print();
    else if(ch == 3) bankers();
    else if(ch == 4) request();
    else exit(0);
}
int main()
{
    while(1) menu();
    return 0;
}
