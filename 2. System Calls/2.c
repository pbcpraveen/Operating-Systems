#include<stdio.h>
#include<unistd.h>
main()
{
    printf("Before fork\n");
    fork();
    printf("Hello world\n");
}

