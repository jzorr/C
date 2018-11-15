/**
 * C file of functions to simulate a load balancer.
 * 
 * @author Orr, Acuna
 * @version 1.0
 */

#include "InstanceHost.h"
#include "LoadBalancer.h"
#include <pthread.h>
#include <stdio.h>

//Creating a jon_node from the struct defined in LoadBalancer.h
job_node* job; //Define node as pointer of data type struct job_node


//global for batch_size
int batch_size, i = 0;
//job_node* arr[batch_size];
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

    //initialize the host instance
    host_init();
}

/**
 * Shuts down the load balancer. Ensures any outstanding batches have
 * completed.
 */
void balancer_shutdown(){
    //TODO
    //pthread_mutex_destroy(&lock); 
    host_shutdown();
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

int job_count = 0;
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
    printf("-------------------------------------------------------------------\n");
    
    //create new job_node for the batch linked list
    job_node* head = NULL;
    head = (job_node*)malloc(sizeof(job_node));
    
    //check if the malloc worked
    if(head == NULL){
        //return 1;
    }
    *data_return = data*data;
    head->user_id = user_id;
    //printf("head->user_id = %d\n", head->user_id);
    head->data = data;
    //printf("head->data = %d\n", head->data);
    //printf("data^2 = %d\n", new_data);
    head->data_result = data_return;
    //printf("head->data_result = %d\n", *data_return);
    head->next = NULL;
    //printf("head->next = %d\n", (int)head->next);

//    //add this job_node to arr[]
//    arr[i]->user_id = user_id;
//    //printf("head->user_id = %d\n", head->user_id);
//    arr[i]->data = data;
//    //printf("head->data = %d\n", head->data);
//    //printf("data^2 = %d\n", new_data);
//    arr[i]->data_result = data_return;
//    //printf("head->data_result = %d\n", *data_return);
//    arr[i]->next = NULL;
//    //printf("head->next = %d\n", (int)head->next); 
    
    
    
    
    // how long is the list 
    job_count++;
    //int list_size = getCount(head);
    //printf("job_count = %d\n", job_count);
    
    //call 'host_request_instance' if the job count is = the set size required for a new instance
    //if(list_size == batch_size){
    if(( job_count % batch_size) == 0){ //job_count
        printf("\n");
        //printf("head->next = %d\n", (int)head->next);
        host_request_instance(head);
    }
    
    //head->data_result = data * data;
    
    //unlock the mutex so it can add another node
    pthread_mutex_unlock(&lock);
    
    // release temp from malloc
    free(head);
    i++;
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


