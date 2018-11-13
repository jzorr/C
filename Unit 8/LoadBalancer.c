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
struct batch {
    int user_id;          //unique id of user
    int data;             //input data provided by user.
    int* data_result;     //pointer to place in global memory to store result.
                          //negative one (-1) means result not computed.
    struct batch* next;//pointer to the next job in a list of jobs.
};

//Creating a Node:
typedef struct batch* job; //Define node as pointer of data type struct LinkedList

//----------------------------------------------------------------------------------------------------------------------
//forward declarations for (public) functions

/**
 * Initializes the load balancer. Takes batch size as parameter.
 * Creates the batch linked list
 */
pthread_mutex_t lock;
void balancer_init(int batch_size){
    
    //create mutex to ensure only one list is added at a time
    pthread_mutex_init(&lock);
    
    //TODO - create a thread for each job within the batch
    pthread_t thr;
    size_t i = 0;
    for(i = 0; i < batch_size; i++){
        //pthread_create(&thr, NULL, balancer_set_batch_size(batch_size), NULL); // this one?
        //---OR---
        pthread_create(&thr, NULL, balancer_add_job, NULL); // or this one?
    }
    
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
    pthread_mutex_destroy(&lock); 
    host_shutdown();
}


/**
 * Helper function to create a new job
 * 
 */
void createJob(){
   job temp; // declare a job
   temp = (job)malloc(sizeof(batch)); // allocate memory using malloc()
   temp.next = NULL;// make next point to NULL
}

int job_counter = 0;  //variable to keep track of the total job count
job head = NULL; //set to NULL initially which will be changed once one is added
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
    
    //create new job for the batch linked list
    job temp,p;// declare two nodes temp and p
    temp = createJob();//createJob will create a new node and next pointing to NULL.
    temp.user_id = user_id;
    temp.data = data;
    temp.data_result = data_return;
    if(head == NULL){
        head = temp;     //when batch is empty
    }
    else{
        p = head;//assign head to p 
        while(p.next != NULL){
            p = p.next;//traverse the list until p is the last node.The last node always points to NULL.
        }
        p.next = temp;//Point the previous last node to the new node created.
    }

    //call 'host_request_instance' if the job count is = the set size required for a new instance
    host_request_instance(job);//TODO
    
    //increment job_counter and use % to determine when to call balancer_set_batch_size
    job_counter++;
    
    //add all the jobs until the linked list is full
    
    //unlock the mutex so it can add another node
    pthread_mutex_unlock(&lock);
    
}

/**
 * Sets the size of the batch. That is, how many jobs much be collected before a
 * server instance requested.
 * 
 * @param size the new batch size.
 */
void balancer_set_batch_size(int size){
    //TODO - % count with size passed to determine when to call for new instance
    if ((job_counter%size) == 0){
        //create new instance
    }
        
    
}


