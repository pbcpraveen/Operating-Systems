#include<stdio.h>
#include<stdlib.h>
typedef struct process {
    int id;
    int st, ft;
}Process;
Process pe[100];
int pid[10], at[10], bt[10], st[10], ft[10], tat[10], rt[10], wt[10];
int curr, n, p_done[10];
float pt = 0, w = 0, t = 0, r = 0, time = 0;
int total = 0, tot = 0;
typedef struct node {
    int data;
    int bt;
    struct node* next;
}Node;
Node *front = NULL;
Node *rear = NULL;
void line(int n)
{
    for(int l = 0; l < n; l++) for(int i = 0; i < 11 + (1/(l+1)); i++) printf("-");
    printf("\n");
}
Node* newNode(int d, int p)
{
    Node *temp = (Node*)malloc(sizeof(Node));
    temp->data = d;
    temp->bt = p;
    temp->next = NULL;
    return temp;
}
void dequeue(Node** front)
{
    Node* temp = *front;
    (*front) = (*front)->next;
    free(temp);
}
void enqueue(Node** front, int d, int p)
{
    Node* start = (*front);
    Node* temp = newNode(d, p);
    if(start==NULL)
    {
        *front=temp;
    }
    else if ((*front)->bt > p)
    {
        temp->next = *front;
        (*front) = temp;
    }
    else {
        while (start->next != NULL &&  start->next->bt <p)
        {
            start = start->next;
        }
        temp->next = start->next;
        start->next = temp;
    }
}
void update()
{
    int flag = 0;
    if(wt[curr] == -1)
    {
        wt[curr] = st[curr] - at[curr];
        rt[curr] = st[curr] - at[curr];
        r += rt[curr];
        flag = 1;
    }
    else wt[curr] = wt[curr]+(pt-ft[curr]);
    ft[curr] = time;
    pe[tot].ft = ft[curr];
    tot++;
    printf("%d \t %d \t %d \t",st[curr],ft[curr],wt[curr]);
    if(bt[curr]!=0)
    {
        printf("--\t");
        p_done[curr] = 1;
    }
    else
    {
        tat[curr] = ft[curr] - at[curr];
        printf("%d\t",tat[curr]);
    }
    if(flag==1)
    {
        rt[curr] = st[curr] - at[curr];
        r = r + rt[curr];
        printf("%d\n",rt[curr]);
    }
    else
    {
        printf("--\n");
    }
    if(bt[curr]==0)
    {
        t += tat[curr];
        w += wt[curr];
    }
    else
    {
        enqueue(&front,curr,bt[curr]);
    }
}
void initialise()
{
    for(int i=0;i<n;i++)
    {
        wt[i]=-1;
        p_done[i] = 0;
    }
}
int alldone()
{
    total=0;
    for (int i=0;i<n;i++)
    {
        if(p_done[i]==0)
            return 0;
    }
    return 1;
}
Node* addprocess(int time)
{
    for(int i = 0; i < n; i++)
    {
        if(at[i] == time)
        {
            if(p_done[i] == 0)
            {
                enqueue(&front,i,bt[i]);
                p_done[i] = 1;
            }
        }
    }
    return front;
}
int main()
{
    time = 0;
    printf("Enter the number of processes: ");
    scanf("%d",&n);
    for(int i = 0; i < n; i++)
    {
        pid[i] = i + 1;
        printf("Enter AT, BT of P%d: ",pid[i]);
        scanf("%d",&at[i]);
        scanf("%d",&bt[i]);
    }
    initialise();
    printf("PID\t AT\t BT\t ST\t FT\t WT\t TAT\t RT\n");
    front = addprocess(time);
    if(front != NULL)
    {
        curr = front->data;
        dequeue(&front);
    }
    else curr = -1;
    while(!alldone()||(front!=NULL)||curr!=-1)
    {
        if(curr != -1)
        {
            pt = time;
            st[curr] = time;
            printf("%d\t %d\t %d\t ",pid[curr],at[curr],bt[curr]);
            pe[tot].id = pid[curr];
            pe[tot].st = st[curr];
            while(bt[curr]>0)
            {
                
                time++;
                bt[curr]--;
                front = addprocess(time);
                if(front != NULL && bt[curr] > bt[front->data])
                    break;
            }
            update();
        }
        else
        {
            time++;
            front = addprocess(time);
        }
        if(front != NULL)
        {
            curr = front->data;
            dequeue(&front);
        }
        else curr = -1;
    }
    w/=n; t/=n; r/=n;
    printf("Average: WT = %.2f TAT = %.2f RT = %.2f\n", w, t, r);
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
        printf("%d         %d ",pe[i].st,pe[i].ft);
    }
    printf("\n");
}
