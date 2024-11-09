#include <linux/btf.h>
#include <linux/btf_ids.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_AUTHOR("Masumi Kanai <masumi.net@gmail.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello world kernel module");

/* Disables missing prototype warnings */
__diag_push();
__diag_ignore_all("-Wmissing-prototypes",
                  "Global kfuncs as their definitions will be in BTF");

struct task_struct *bpf_find_get_task_by_vpid(pid_t nr) {
  printk(KERN_ALERT "Hello in bpf_find_get_task_by_vpid!\n");
  return 0;
  // return find_get_task_by_vpid(nr);
}

__diag_pop();

BTF_SET8_START(bpf_task_set)
BTF_ID_FLAGS(func, bpf_get_task_pid, KF_ACQUIRE | KF_RET_NULL)
BTF_ID_FLAGS(func, bpf_put_pid, KF_RELEASE)
BTF_SET8_END(bpf_task_set)

static const struct btf_kfunc_id_set bpf_task_kfunc_set = {
    .owner = THIS_MODULE,
    .set = &bpf_task_set,
};

static int mymodule_init(void) {
  printk(KERN_ALERT "Hello world!\n");
  return register_btf_kfunc_id_set(BPF_PROG_TYPE_TRACING, &bpf_task_kfunc_set);
  return 0;
}

static void mymodule_exit(void) { 
  printk(KERN_INFO "Goodbye world 1.\n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
