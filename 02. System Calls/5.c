#include<stdio.h>
#include<unistd.h>
main()
{
    pid_t pro_id;
    pro_id = fork();
    if(pro_id == 0)
    {
        printf("Child ID: %d Parent ID: %d \n",getpid(),getppid());
    }
    else if(pro_id > 0)
    {
        printf("Parent ID: %d Parent's Parent ID: %d \n",getpid(),getppid());
    }
    else printf("Fork failure\n");
}
