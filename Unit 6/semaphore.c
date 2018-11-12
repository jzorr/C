#include <unistd.h>  
#include <stdlib.h>  
#include <semaphore.h>
#include <stdio.h>  
#include <unistd.h>

struct mutex_lock; 

sem_t sem;
/* initialize a private semaphore */ 
int ret;
int count = 2; 

int main(int argc, char *argv[]) {     
 // Assume successful initialization of semaphore.
 if (sem_init(&sem, 1, count)) {
  printf("Initialized shared Semaphore!\n");
 }
 pid_t anotherProcess = fork();

 if (anotherProcess == 0) {
    ret = sem_wait(&sem); /* wait for semaphore */
  printf("I'm critical to child, I guess I'm special?");
 } else if (anotherProcess != 0) {
  sem_wait(&sem); /* wait for semaphore */
  printf("I'm a critical section of code, I am special.\n");
  // increment semaphore to release
  ret = sem_post(&sem);
 }
 return 0; 
}

void acquire(mutex_lock* m) {
  while (test_and_set(&m->lock));
}

void release(mutex_lock* m) {
  m->lock = false;
}