/**
 * Header file definition of functions to simulate a cloud-like server instance
 * host.
 * 
 * @author Acuna
 * @version 1.0
 */

#ifndef INSTANCEHOST_H
#define INSTANCEHOST_H

#include "LoadBalancer.h"

struct job_node; //defined in LoadBalancer

//forward declarations for (public) functions

/**
* Initializes the host environment.
*/
void host_init();

/**
* Shuts down the host environment. Ensures any outstanding batches have
* completed.
*/
void host_shutdown();

/**
* Creates a new server instance (i.e., thread) to handle processing the items
* contained in a batch (i.e., a listed list of job_node). InstanceHost will
* maintain a list of active instances, and if the host is requested to
* shutdown, ensures that all jobs are completed.
*
* @param job_batch_list A list containing the jobs in a batch to process.
*/
void host_request_instance(struct job_node* batch);

#endif