#include<stdio.h>
typedef struct process
{
    int id;
    float at, bt, st, ft, wt, tat, rt;
}Process;
Process p[100], pe[100];
int N = 0, ts = 1;
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
        printf("Enter AT and BT of P%d: ", i+1);
        scanf("%f %f", &(p[i].at), &(p[i].bt));
        p[i].id = i + 1;
    }
    printf("Time slice: ");
    scanf("%d", &ts);
}
void rr()
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
    int tot = 0, c = N, qn = 1, t = p[0].at, V[100] = {0}, cc = 0;
    Process qu[N];
    qu[0] = p[0];
    pe[0] = p[0];
    while(c != 0) {
        cc = 0;
        for(int i = qn; i < N; i++)
        {
            if(p[i].at <= t) {
                qu[qn] = p[i];
                qn++;
            }
        }
        for(int i = 0; i < qn; i++)
        {
            if(V[i] != -1) {
                pe[tot].id = qu[i].id;
                pe[tot].at = qu[i].at;
                pe[tot].bt = qu[i].bt;
                if(tot == 0) {
                    pe[tot].st = qu[i].at;
                    pe[tot].ft = (qu[i].bt > ts) ? (qu[i].at + ts) : (qu[i].at + qu[i].bt);
                    qu[i].bt -= ts;
                    pe[tot].wt = 0;
                    pe[tot].rt = 0;
                    if(qu[i].bt <= 0) pe[tot].tat = pe[tot].ft - pe[tot].at;
                    else pe[tot].tat = -1;
                    if(pe[tot].tat != -1) qu[i].tat = pe[tot].tat;
                    if(pe[tot].rt != -1) qu[i].rt = pe[tot].rt;
                    qu[i].wt = 0;
                    qu[i].ft = pe[tot].ft;
                    V[i] = 1;
                    if(qu[i].bt <= 0){ V[i] = -1; c--;}
                }
                else {
                    if(pe[tot].at <= pe[tot-1].ft) pe[tot].st = pe[tot-1].ft;
                    else pe[tot].st = pe[tot].at;
                    pe[tot].ft = (qu[i].bt > ts) ? (pe[tot].st + ts) : (pe[tot].st + qu[i].bt);
                    qu[i].bt -= ts;
                    if(V[i] == 1) pe[tot].wt = qu[i].wt + (pe[tot].st - qu[i].ft);
                    else pe[tot].wt = pe[tot].st - pe[tot].at;
                    if(V[i] == 0) pe[tot].rt = pe[tot].st - pe[tot].at;
                    else pe[tot].rt = -1;
                    if(qu[i].bt <= 0) pe[tot].tat = pe[tot].ft - pe[tot].at;
                    else pe[tot].tat = -1;
                    qu[i].ft = pe[tot].ft;
                    qu[i].wt = pe[tot].wt;
                    if(pe[tot].tat != -1) qu[i].tat = pe[tot].tat;
                    if(pe[tot].rt != -1) qu[i].rt = pe[tot].rt;
                    V[i] = 1;
                    if(qu[i].bt <= 0){ V[i] = -1; c--;}
                }
                tot++; t+= ts; cc = 1;
            }
            for(int i = qn; i < N; i++)
            {
                if(p[i].at <= t) {
                    qu[qn] = p[i];
                    qn++;
                }
            }
        }
        if(cc == 0) t += 1;
    }
    printf("\nRR Scheduling:\nPID \t AT \t BT \t ST \t FT \t WT \t TAT \t RT\n");
    for(int i = 0; i < tot; i++) {
        if(pe[i].tat != -1) {
            avgtat += pe[i].tat;
            avgwt += pe[i].wt;
        }
        if(pe[i].rt > 0) avgrt += pe[i].rt;
    }
    avgwt/=N; avgtat/=N; avgrt/=N;
    for(int i = 0; i < tot; i++)
    {
        printf("P %d \t %.2f \t %.2f \t %.2f \t %.2f \t ", pe[i].id, pe[i].at, pe[i].bt, pe[i].st, pe[i].ft);
        if(pe[i].wt < 0)
        {
            printf("-- \t ");
        }
        else {
            printf("%.2f \t ",pe[i].wt);
        }
        if(pe[i].tat < 0)
        {
            printf("-- \t ");
        }
        else {
            printf("%.2f \t ",pe[i].tat);
        }
        if(pe[i].rt < 0)
        {
            printf("-- \t ");
        }
        else {
            printf("%.2f \t ",pe[i].rt);
        }
        printf("\n");
    }
    printf("Average: WT = %3.2f TAT = %3.2f RT = %3.2f\n\n", avgwt, avgtat, avgrt);
    printf("Gantt chart:\n");
    line(tot);
    for(int i = 0; i <= 2; i++)
    {
        if(i==1) { for(int j = 0; j < tot; j++) printf("|    P%d    ", pe[j].id); printf("|"); }
        else { for(int j = 0; j < tot; j++) printf("|          "); printf("|"); }
        printf("\n");
    }
    line(tot);
    for(int i = 0; i < tot; i++)
    {
        printf("%.1f     %.1f ",pe[i].st,pe[i].ft);
    }
    printf("\n");
}
int main()
{
    input();
    rr();
}
