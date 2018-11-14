/**
 * C file of functions to simulate a cloud-like server instance
 * host.
 * 
 * @author Orr
 * @version 1.0
 */


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "InstanceHost.h"
#include "LoadBalancer.h"

//struct job_node* batch; //defined in LoadBalancer

pthread_mutex_t* lock1;

//forward declarations for (public) functions

/**
* Initializes the host environment.
*/
void host_init(){
    //TODO
    //pthread_mutex_init(&lock, NULL);
}

/**
* Shuts down the host environment. Ensures any outstanding batches have
* completed.
*/
void host_shutdown(){
    //TODO
    //pthread_mutex_destroy(&lock);
}

void* functionA(void* arg){
    pthread_mutex_lock(lock1);
   
    printf("batch->data = %d \n", (int)arg); 
            
    pthread_mutex_unlock(lock1);
    pthread_exit(NULL);
    
}

/**
* Creates a new server instance (i.e., thread) to handle processing the items
* contained in a batch (i.e., a listed list of batch). InstanceHost will
* maintain a list of active instances, and if the host is requested to
* shutdown, ensures that all jobs are completed.
*
* @param job_batch_list A list containing the jobs in a batch to process.
*/
void host_request_instance(struct job_node* batch){
    printf("LoadBalancer: Received batch and spinning up new instance.\n");
    //printf("batch = %d\n", (int*)batch);

    pthread_t thr;
    lock1 = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
    
    //create mutex to ensure only one list is added at a time
    pthread_mutex_init(lock1, NULL);
    
    if(batch->next != NULL){  
        printf("batch->next = %d\n", (int)batch->next);
        pthread_create(&thr, NULL, &functionA, (void*)batch->data); //(int*)batch->data)
        pthread_join(thr, NULL);          
    }
    pthread_mutex_destroy(lock1);
    free(lock1);
}

