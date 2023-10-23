#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// THREAD function to ping a host
void *perform_ping(void *arguments) {
    pid_t r;
    char *ip = (char *)arguments;
    printf("IN THREAD: Pinging host IP:%s started\n", ip);
    r = fork();  // Create the child process
    if (r<0){ 
    	// Handle the error case
	//(...)
	pthread_exit(NULL);
    } 
    else if(r==0){  
    	// Execute "ping" in the child process using execlp() system call
        //(...)
	exit(0); 
    }
    else{ 
    	// Wait for the child process before exiting
        //(...)
    	printf("IN THREAD: Pinging host IP:%s completed\n", ip);
    	pthread_exit(NULL);
    }
}

// MAIN function to create threads
int main(int argc, char** argv) {
    // Printing command-line arguments (i.e. IP addresses)
    int k;
    printf("IN MAIN: The IP addresses are:\n");
    for (k = 1; k < argc; k++) {
        printf("%s\n", argv[k]);
    }

    // Create threads to ping each host
    pthread_t threads[argc];
    int i;
    for (i = 1; i < argc; i++) {
            printf("IN MAIN: Creating thread %d to ping IP address: %s\n", i, argv[i]);
            int r = pthread_create(&threads[i], NULL, perform_ping, argv[i]);
            if (r == 0) {
                //print thread number
            } else {
                //print error
            }        
    }
    // Wait for each thread to complete
    int j;
    for (j = 1; j < argc; j++) { 
            pthread_join(threads[j], NULL);
            printf("IN MAIN: Thread %d has ended.\n", j);
    }
    printf("IN MAIN: Program has ended.\n");
    return 0;
}


