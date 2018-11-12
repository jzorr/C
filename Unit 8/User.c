/**
 * Program to simulate multiple users simultaneously requesting work (a "job")
 * to be carried by a load balancing server and returned to the user. Job is to
 * compute the square of a number.
 * 
 * @author Khan, Acuna
 * @version 1.0
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "LoadBalancer.h"

//forward declarations for internal (private) functions.
void* simulate_user_request(void* user_id);

/**
 * Entry point to simulation.
 * 
 * @return Zero.
 */
int main() {
    int number_of_requests = 10;
    int batch_size = 5;
    printf("Please input number of requests (users): ");
    //scanf("%d", &number_of_requests);
    printf("Please input batch size: ");
    //scanf("%d", &batch_size);

    pthread_t threads[number_of_requests];

    balancer_init(batch_size);

    //create number_of_requests number of users that want to square a number.
    for (int i = 0; i < number_of_requests; i++) {
        printf("creating: %d\n", i);
        pthread_create(&threads[i], NULL, &simulate_user_request, (void*)i);
    }

    balancer_shutdown();

    //wait for all users to finish before program exit.
    for (int i = 0; i < number_of_requests; i++)
        //pthread_join(threads[i], NULL);   
    
    return 0;
}

/**
 * Simulates a user requesting work to be done a server. Expected to be run in a
 * thread.
 * 
 * @param user_id
 * @return 
 */
void* simulate_user_request(void* user_id) {
    int data = rand() % 100;
    int* result = (int*)malloc(sizeof(int));
    *result = -1;
    
    //make the thread wait to simulate differences in when user requests occur.
    int ms = (rand() % 100) * 1000;
    usleep(ms);
    
    printf("User #%d: Wants to process data=%d and store it at %p.\n", (int)user_id, data, result);
    
    //make request to balance to complete job and wait for it's completion.
    balancer_add_job((int)user_id, data, result);
    while(*result == -1);  //busy waiting, bad but simple
    
    printf("User #%d: Received result from data=%d as result=%d.\n", (int)user_id, data, *result);
    
    free(result);
    
    pthread_exit(NULL);
}
