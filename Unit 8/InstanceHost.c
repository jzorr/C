/**
 * C file of functions to simulate a cloud-like server instance
 * host.
 * 
 * @author Orr
 * @version 1.0
 */

#include <pthread.h>
#include "InstanceHost.h"

struct batch; //defined in LoadBalancer

pthread_mutex_t lock;

//forward declarations for (public) functions

/**
* Initializes the host environment.
*/
void host_init(){
    //TODO
}

/**
* Shuts down the host environment. Ensures any outstanding batches have
* completed.
*/
void host_shutdown(){
    //TODO
    pthread_mutex_destroy(&lock);
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
    //traverse the batch passed from head-to-tail
    while(batch->next != NULL){
        pthread_t thr;
        pthread_create(&thr, NULL, host_request_instance, NULL); // might need to change the last NULL
        batch = batch->next;
    }

    //create mutex to ensure only one list is added at a time
    pthread_mutex_init(&lock);
    
//    //TODO - create a thread for each job within the batch
//    pthread_t thr;
//    size_t i = 0;
//    for(i = 0; i < batch_size; i++){
//        pthread_create(&thr, NULL, host_request_instance, NULL); // might need to change the last NULL
//    }
    
}