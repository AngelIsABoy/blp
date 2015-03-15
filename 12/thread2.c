#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void *thread_function();

int run_now = 1;

int main(){
    int res;
    pthread_t a_thread;
  //  void *thread_result;
    
    res = pthread_create(&a_thread, NULL, thread_function, NULL);
    if(res != 0) {
       perror("Thread creation failed\n");
       exit(EXIT_FAILURE);
    }

 
    int print_count1 = 0;

    while (print_count1++ < 20) {
        if (run_now == 1){
            printf("1");
            run_now = 2;
         } else {
            sleep(1); 
         }
    }

    printf("\nWaiting for thread to finish...\n");
    res = pthread_join(a_thread,NULL);
    if(res != 0) {
        perror("Thread join failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Thread joined.");
  //  printf("Message is now %s\n", message);
    exit(EXIT_SUCCESS);
}

void *thread_function(){
    int print_count2 = 0;

    while(print_count2++ < 20) {
        if (run_now == 2) {
            printf("2");
            run_now = 1;
        } else {
            sleep(1);
        }
    }
   // printf("thread_function is running. Argument was %s\n", (char *)arg);
   // sleep(3);
   // strcpy(message, "Bye!");
   // pthread_exit("Thank you for CPU time");
}
