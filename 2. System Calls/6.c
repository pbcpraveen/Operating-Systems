#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
main()
{
    pid_t p;
    p = fork();
    if(p == 0)
    {
        sleep(2);
        printf("Hello after 2s!\n");
    }
    else if(p > 0)
    {
        printf("Hello!\n");
        wait(NULL);
        printf("Child over, now exit.\n");
        exit(0);
    }
}
