#include<stdio.h>
typedef struct process
{
	int id;
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
		printf("Enter AT and BT of P%d: ", i+1);
		scanf("%f %f", &(p[i].at), &(p[i].bt));
		p[i].id = i + 1;
	}
}
void fcfs()
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
	p[0].st = p[0].at;
	p[0].ft = p[0].st + p[0].bt;
	p[0].wt = 0;
	p[0].rt = 0;
	p[0].tat = p[0].ft - p[0].at;
	avgwt = p[0].wt; avgtat = p[0].tat; avgrt = p[0].rt;
	for(int i = 1; i < N; i++)
	{
        p[i].st = (p[i-1].ft > p[i].at) ? p[i-1].ft : p[i].at;
		p[i].ft = p[i].st + p[i].bt;
		p[i].wt = p[i].st - p[i].at;
		p[i].rt = p[i].wt;
		p[i].tat = p[i].ft - p[i].at;
		avgwt += p[i].wt; avgtat += p[i].tat; avgrt += p[i].rt;
	}
	printf("\nFCFS Scheduling:\nPID \t AT \t BT \t ST \t FT \t WT \t TAT \t RT\n");
	avgwt/=N; avgtat/=N; avgrt/=N;
	for(int i = 0; i < N; i++)
	{
		printf("P %d \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f \t %.2f", p[i].id, p[i].at, p[i].bt, p[i].st, p[i].ft, p[i].wt, p[i].tat, p[i].rt);
		printf("\n");
	}
	printf("Average: WT = %3.2f TAT = %3.2f RT = %3.2f\n\n", avgwt, avgtat, avgrt);
    printf("Gantt chart:\n");
    line(N);
    for(int i = 0; i <= 2; i++)
    {
        if(i==1) { for(int j = 0; j < N; j++) printf("|    P%d    ", p[j].id); printf("|"); }
        else { for(int j = 0; j < N; j++) printf("|          "); printf("|"); }
        printf("\n");
    }
    line(N);
    for(int i = 0; i < N; i++)
    {
        printf("%.1f     %.1f ",p[i].st,p[i].ft);
    }
    printf("\n");
}
int main()
{
	input();
	fcfs();
}
