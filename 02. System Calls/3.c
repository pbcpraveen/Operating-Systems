#include<stdio.h>
#include<unistd.h>
main()
{
    pid_t pro_id;
    printf("Before fork\n");
    pro_id = fork();
    if(pro_id == 0) // Child process
    {
        printf("Hello world from child\n");
    }
    else if(pro_id > 0) // parent process
    {
        printf("Hello world from parent\n");
    }
    else
        printf("Fork failure\n");
}
