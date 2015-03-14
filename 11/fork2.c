#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    pid_t pid;
    char *message;
    int n;

    printf("fork program starting\n");
    pid = fork();
    switch(pid) {
    case -1:
        perror("fork failed");
        exit(1);
    case 0:
        message = "This is the child";
        n = 3;
        break;
    default:
        message = "This is the parent";
        n = 10;
        break;
    }
    for (; n > 0; n--) {
        if (n > 3 && n < 6)
            system("ps ax");
        puts(message);
        sleep(1);
    }
    exit(0);
}
