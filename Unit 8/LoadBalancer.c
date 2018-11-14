/**
 * C file of functions to simulate a load balancer.
 * 
 * @author Orr, Acuna
 * @version 1.0
 */

#include <pthread.h>
#include "LoadBalancer.h"
#include "InstanceHost.h"

//structure to track jobs as they are created. serves as a linked list node.
struct job_node {
    int user_id;          //unique id of user
    int data;             //input data provided by user.
    int* data_result;     //pointer to place in global memory to store result.
                          //negative one (-1) means result not computed.
    struct job_node* next;//pointer to the next job in a list of jobs.
};

//Creating a Node:
typedef struct job_node* job; //Define node as pointer of data type struct job_node

//global for batch_size
int batch_size;

//----------------------------------------------------------------------------------------------------------------------
//forward declarations for (public) functions

/**
 * Initializes the load balancer. Takes batch size as parameter.
 * Creates the batch linked list
 */
pthread_mutex_t lock;
void balancer_init(int batch_size){
    
    // initialize the batch size
    balancer_set_batch_size(batch_size);
    
    //create mutex to ensure only one list is added at a time
    pthread_mutex_init(&lock);
    
    //TODO - create a thread for each job within the batch
    pthread_t thr;
    size_t i = 0;
    for(i = 0; i < batch_size; i++){
        pthread_create(&thr, NULL, balancer_set_batch_size, batch_size); // this one?
        //---OR---
        pthread_create(&thr, NULL, balancer_add_job, NULL); // or this one?
    }
    
    //initialize the host instance
    host_init();
}

/**
 * Shuts down the load balancer. Ensures any outstanding batches have
 * completed.
 */
void balancer_shutdown(){
    //TODO
    pthread_mutex_destroy(&lock); 
    host_shutdown();
}

/**
 * Adds a job to the load balancer. If enough jobs have been added to fill a
 * batch, will request a new instance from InstanceHost. When job is complete,
 * *data_return will be updated with the result.
 * 
 * @param user_id the id of the user making the request.
 * @param data the data the user wants to process.
 * @param data_return a pointer to a location to store the result of processing.
 */
void balancer_add_job(int user_id, int data, int* data_return){
    //TODO
    // lock the mutex so it can only add one at a time
    pthread_mutex_lock(&lock);
    
    //print the job and what it is requesting
    printf("LoadBalancer: Received new job from user #%d to process data = #%d and store it at %p.\n", user_id, data, data_return);
    
    //create new job_node for the batch linked list
    job_node* head = NULL;
    head = (job_node*)malloc(sizeof(job_node));
    
    //check if the malloc worked
    if(head == NULL){
        return 1;
    }
    
    head->data = data;
    head->user_id = user_id;
    head->data_result = data_return;
    head->next = NULL;

    // how long is the list 
    int list_size = getCount(head);
    
    //call 'host_request_instance' if the job count is = the set size required for a new instance
    if(list_size == batch_size){
            host_request_instance(head);
    }
    
    // release temp from malloc
    free(head);
    
    //unlock the mutex so it can add another node
    pthread_mutex_unlock(&lock);
}

/**
 * Counts the nodes in the linked list
 *
 * @param head the job_node linked list
 */
int getCount(struct job_node* head){
    int count = 0; //initialize count
    struct job_node* current = head; //initialize current
    while(current != NULL){
        count++;
        current = current->next;
    }
    return count;
}


/**
 * Sets the size of the batch. That is, how many jobs must be collected before a
 * server instance requested.
 * 
 * @param size the new batch size.
 */
void balancer_set_batch_size(int size){
    //TODO - % count with size passed to determine when to call for new instance
    batch_size = size;    
}


