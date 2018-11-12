#include <linux/module.h>
#include <linux/printk.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>

static int inp_pid;

module_param(inp_pid, int, 0);

static int __init ex_init(void) {
    struct task_struct *task;
    struct task_struct *child_task;
    struct list_head *child_iter;
    
    for_each_process(task) {
        if (task->pid > inp_pid && task->state != 0) {
            pr_info("PROCESS\t\tPID\tSTATE\tPRIO\tST_PRIO\tNORM_PRIO\n");
            pr_info("%-16s %-10d %-5ld %-6u %-6u %-6u\n", task->comm, task->pid, task->state, task->prio, task->static_prio, task->normal_prio);

            list_for_each(child_iter, &task->children) {
                child_task = list_entry(child_iter, struct task_struct, sibling);
                pr_info("CHILD\n");
                pr_info("%-16s %-10d %-5ld %-6u %-6u %-6u\n", child_task->comm, child_task->pid, child_task->state, child_task->prio, child_task->static_prio, child_task->normal_prio);
            }

            pr_info("PARENT\n");
            pr_info("%-16s %-10d %-5ld %-6u %-6u %-6u\n\n", task->parent->comm, task->parent->pid, task->parent->state, task->parent->prio, task->parent->static_prio, task->parent->normal_prio);

            printk("\n");
        }
    }

    return 0;
}

static void __exit ex_fini(void) {
	printk("Removing Module.\n");
}

module_init(ex_init);
module_exit(ex_fini);