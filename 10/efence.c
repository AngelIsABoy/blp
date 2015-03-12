#include<stdio.h>
#include<stdlib.h>

int main(){
    char *ptr = (char *) malloc(1024);
    ptr[0] = 0;

    /* Now write beyond the block */
    ptr[1024] = 0;
    exit(0);
}

/* This is a bad program and I can not test it.
 * I did not install the lib of
 *  ElectricFence .
 *  */
