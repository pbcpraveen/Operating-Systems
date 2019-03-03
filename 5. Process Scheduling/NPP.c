#include<stdio.h>
typedef struct process
{
    int id, p, v;
    float at, bt, st, ft, wt, tat, rt;
}Process;
Process p[100];
int N = 0;
void line(int n)
{
    for(int l = 0; l < n; l++) for(int i = 0; i < 11 + (1/(l+1)); i++) printf("-");
    printf("\n");
}
void input()
{
    printf("No. of processes: ");
    while(N == 0) scanf("%d", &N);
    for(int i = 0; i < N; i++)
    {
        printf("Enter AT, BT and P of P%d: ", i+1);
        scanf("%f %f %d", &(p[i].at), &(p[i].bt), &(p[i].p));
        p[i].id = i + 1; p[i].v = 0;
    }
}
void sort(Process p[], int r)
{
    for(int i = 0; i < r - 1; i++)
        for(int j = 0; j < r - 1; j++)
            if(p[j].p > p[j+1].p)
            {
                Process t = p[j];
                p[j] = p[j+1];
                p[j+1] = t;
            }
}
void npp()
{
    for(int i = 0; i < N - 1; i++)
        for(int j = 0; j < N - 1; j++)
            if(p[j].at > p[j+1].at)
            {
                Process t = p[j];
                p[j] = p[j+1];
                p[j+1] = t;
            }
    float avgwt, avgtat, avgrt;
    int c = 0, r = 0, ch = 0, i0 = 0;
    Process q[N], pq[N];
    q[0] = p[0];
    pq[0] = p[0];
    for(int i = 1; i < N; i++) {
        if(p[i].at <= q[0].at && p[i].p < q[0].p)
        {    q[0] = p[i]; i0 = i; }
    }
    p[i0].v = 1;
    q[0].v = 1;
    int t = q[0].at;
    do
    {
        ch = 0;
        if(c == 0) {
            q[0].st = q[0].at;
            q[0].ft = q[0].st + q[0].bt;
            q[0].wt = 0;
            q[0].rt = 0;
            q[0].tat = q[0].bt;
            t += q[0].bt;
            c++;
            ch = 1;
            avgwt = 0; avgrt = 0; avgtat = q[0].tat;
        }
        else if(r > 0) {
            q[c] = pq[0];
            q[c].st = (q[c].at > q[c-1].ft) ? q[c].at : q[c-1].ft;
            q[c].ft = q[c].st + q[c].bt;
            q[c].wt = q[c].st - q[c].at;
            q[c].rt = q[c].wt;
            q[c].tat = q[c].ft - q[c].at;
            t += q[c].bt;
            c++;
            ch = 1;
            avgwt += q[c-1].wt; avgrt += q[c-1].rt; avgtat += q[c-1].tat;
        }
        if(ch == 0) t++;
        if(ch == 1 && c > 0) {
            for(int i = 1; i < r; i++) {
                pq[i-1] = pq[i];
            }
            if(r > 0) r--;
        }
        for(int i = 0; i < N; i++)
        {
            if(p[i].v == 0 && p[i].at <= t) {
                p[i].v = 1;
                pq[r] = p[i];
                r++;
            }
        }
        sort(pq,r);
    }while(c < N);
    printf("\nNPP Scheduling:\nPID \t P \t AT \t BT \t ST \t FT \t WT \t TAT \t RT\n");
    avgwt/=N; avgtat/=N; avgrt/=N;
    for(int i = 0; i < N; i++)
    {
        printf("P %d \t %d \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f", q[i].id, q[i].p, q[i].at, q[i].bt, q[i].st, q[i].ft, q[i].wt, q[i].tat, q[i].rt);
        printf("\n");
    }
    printf("Average: WT = %3.2f TAT = %3.2f RT = %3.2f\n\n", avgwt, avgtat, avgrt);
    printf("Gantt chart:\n");
    line(N);
    for(int i = 0; i <= 2; i++)
    {
        if(i==1) { for(int j = 0; j < N; j++) printf("|    P%d    ", q[j].id); printf("|"); }
        else { for(int j = 0; j < N; j++) printf("|          "); printf("|"); }
        printf("\n");
    }
    line(N);
    for(int i = 0; i < N; i++)
    {
        printf("%.1f     %.1f ",q[i].st,q[i].ft);
    }
    printf("\n");
}
int main()
{
    input();
    npp();
}

