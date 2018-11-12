/**
 * C file of functions to simulate a load balancer.
 * 
 * @author Orr
 * @version 1.0
 */

# include "LoadBalancer.h"
# include "InstanceHost.h"

//structure to track jobs as they are created. serves as list node.
struct job_node {
    int user_id;          //unique id of user
    int data;             //input data provided by user.
    int* data_result;     //pointer to place in global memory to store result.
                          //negative one (-1) means result not computed.
    struct job_node* next;//pointer to the next job in a list of jobs.
};

//forward declarations for (public) functions

/**
 * Initializes the load balancer. Takes batch size as parameter.
 */
void balancer_init(int batch_size){
    //TODO
    pthread_t thr;
    size_t i = 0;
    for(i = 0; i < batch_size; i++){
        pthread_create(&thr, NULL, balancer_set_batch_size(batch_size), NULL);
    }
    
    
}

/**
 * Shuts down the load balancer. Ensures any outstanding batches have
 * completed.
 */
void balancer_shutdown(){
    //TODO
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
    
    //print the job and what it is requesting
    printf("LoadBalancer: Received new job from user #%d to process data = #%d and store it at %p.\n". user_id, data, data_return);
    
    //create new job_node for the linked list
    job_node job;
    job.user_id = user_id;
    job.data = data;
    job.data_result = data_return; 
    
}

/**
 * Sets the size of the batch. That is, how many jobs much be collected before a
 * server instance requested.
 * 
 * @param size the new batch size.
 */
void balancer_set_batch_size(int size){
    //TODO
    
}


