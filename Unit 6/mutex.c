struct mutex_lock;

struct mutex_lock create_mutex(); // how do it implement this? 

void acquire(mutex_lock* m);

void release_mutex(lutex_lock* m);



mutex_lock lock;

int counter;

int main()
{
    lock = create_mutex();
    acquire(&lock);
    
    unsigned long i = 0;
    counter += 1;
    printf("\n %d start \n", counter);
    
    for(i = 0; i < (xFFFFFFFF); i++);
    
    printf("\n %d end \n", counter);
    
    release_mutex(&lock);
}
