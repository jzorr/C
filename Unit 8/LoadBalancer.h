/**
 * Header file definition of functions to simulate a load balancer.
 * 
 * @author Khan, Acuna
 * @version 1.0
 */

#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include "InstanceHost.h"

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
void balancer_init(int batch_size);

/**
 * Shuts down the load balancer. Ensures any outstanding batches have
 * completed.
 */
void balancer_shutdown();

/**
 * Adds a job to the load balancer. If enough jobs have been added to fill a
 * batch, will request a new instance from InstanceHost. When job is complete,
 * *data_return will be updated with the result.
 * 
 * @param user_id the id of the user making the request.
 * @param data the data the user wants to process.
 * @param data_return a pointer to a location to store the result of processing.
 */
void balancer_add_job(int user_id, int data, int* data_return);

/**
 * Sets the size of the batch. That is, how many jobs much be collected before a
 * server instance requested.
 * 
 * @param size the new batch size.
 */
void balancer_set_batch_size(int size);

#endif /* LOADBALANCER_H */
