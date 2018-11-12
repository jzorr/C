#include <linux/module.h>
#include <linux/sched/signal.h>

void myFunc(void)
{
    struct task_struct* task = current;
    struct task_struct* task_parent;
    size_t process_counter = 0;

    for_each_process(task)
    {
        printk(KERN_INFO "CURRENT PROCESS = [%s], PID = [%d], STATE = [%li], PRIO = [%d], ST-PRIO = [%d], NO-PRIO = [%d]\n", task->comm, task->pid, task->state, task->prio, task->static_prio, task->normal_prio);
        task_parent = task->parent;
        printk(KERN_INFO "PARENT PROCESS = [%s], PID = [%d], STATE = [%li], PRIO = [%d], ST-PRIO = [%d], NO-PRIO = [%d]\n", task_parent->comm, task_parent->pid, task_parent->state, task_parent->prio, task_parent->static_prio, task_parent->normal_prio);
        printk("-------------------------------------------------------");
        ++process_counter;
    }
    printk(KERN_INFO "++ Number of process: %zu\n", process_counter);
}

/*this is called when the module is loaded*/
int simple_init(void)
{
    printk(KERN_INFO "Loading Module\n");
    myFunc();
    return 0;
}

/* this is called when the module is removed*/
void simple_exit(void)
{
    printk(KERN_INFO "Removing module\n");
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("SIMPLE MODULE");
MODULE_AUTHOR("JOHN");


