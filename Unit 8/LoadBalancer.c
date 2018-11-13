/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * C file of functions to simulate a load balancer.
 * 
 * @author Orr
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


//function to create a new node
 job_node createNode(){
     job_node temp; // declare a node
     temp = (job_node)malloc(sizeof(batch_size)); // allocate memory using malloc()
     temp->next = NULL;// make next point to NULL
     return temp;//return the new node
 }

//function to add a node to the LinkedList -- tied into balancer_add_job
job_node addNode(job_node head, int value){
    job_node temp,p;// declare two nodes temp and p
    temp = createNode();//createNode will return a new node with data = value and next pointing to NULL.
    temp->data = value; // add element's value to data part of node
    if(head == NULL){
        head = temp;     //when linked list is empty
    }
    else{
        p  = head;//assign head to p 
        while(p->next != NULL){
            p = p->next;//traverse the list until p is the last node.The last node always points to NULL.
        }
        p->next = temp;//Point the previous last node to the new node created.
    }
    return head;
}
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
        pthread_create(&thr, NULL, balancer_set_batch_size(batch_size), NULL); // this one?
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
 * Adds a job to the load balancer. If enough jobs have been added to fill a
 * batch, will request a new instance from InstanceHost. When job is complete,
 * *data_return will be updated with the result.
 * 
 * @param user_id the id of the user making the request.
 * @param data the data the user wants to process.
 * @param data_return a pointer to a location to store the result of processing.
 */

int job_counter = 0; 

void balancer_add_job(int user_id, int data, int* data_return){
    //TODO
    // lock the mutex so it can only add one at a time
    pthread_mutex_lock(&lock);
    
    //print the job and what it is requesting
    printf("LoadBalancer: Received new job from user #%d to process data = #%d and store it at %p.\n", user_id, data, data_return);
    
    //create new job_node for the batch linked list
    job_node job;
    job = (job_node)malloc(sizeof(struct job_node)); // allocate memory using malloc()
    job.user_id = user_id;
    job.data = data;
    job.data_result = data_return;
    job.next = NULL; //pointer to the next node in the linked list set to NULL
    
    //call 'host_request_instance' if the job count is = the set size required for a new instance
    host_request_instance();
    
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


