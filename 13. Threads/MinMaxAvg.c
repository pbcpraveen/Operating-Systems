#include<pthread.h> 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int max, min, l;
float avg;
int list[10];
void *Max(void *param);
void *Min(void *param);
void *Avg(void *param);
int main(int argc, char *argv[]) 
{ 
	pthread_t tid1, tid2, tid3;
	pthread_attr_t attr1, attr2, attr3;
	if (argc < 2) 
	{ 
		fprintf(stderr,"Usage: Enter list of integer values\n"); 
		return -1; 
	}
	for(int i = 1; i < argc; i++) list[i-1] = atoi(argv[i]);
	l = argc - 1;
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);
	pthread_attr_init(&attr3); 
	pthread_create(&tid1,&attr1,Max, list);
	pthread_create(&tid2,&attr2,Min, list);
	pthread_create(&tid3,&attr3,Avg, list);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid3,NULL); 
	printf("Max, Min, Avg: %d, %d, %f\n",max,min,avg);
} 
void *Max(void *param)
{ 
	max = list[0];
	for(int i = 1; i < l; i++)
	{
		if(max < list[i]) max = list[i];
	}
	pthread_exit(0);
}
void *Min(void *param)
{ 
	min = list[0];
	for(int i = 1; i < l; i++)
	{
		if(min > list[i]) min = list[i];
	}
	pthread_exit(0);
} 
void *Avg(void *param)
{
	avg = 0;
	for(int i = 0; i < l; i++)
	{
		avg += list[i];
	}
	avg /= l;
	pthread_exit(0); 
} 

