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

__bpf_kfunc int bpf_hello(int id) {
  printk(KERN_ALERT "hello from eBPF (id=%d)", id);
  return 0;
}
__bpf_kfunc int bpf_hello_const(int id__k) {
  printk(KERN_ALERT "hello_const from eBPF (id=%d)", id__k);
  return 0;
}

__diag_pop();

BTF_SET8_START(bpf_task_set)
BTF_ID_FLAGS(func, bpf_hello)
BTF_ID_FLAGS(func, bpf_hello_const)
BTF_SET8_END(bpf_task_set)


static const struct btf_kfunc_id_set bpf_task_kfunc_set = {
    .owner = THIS_MODULE,
    .set = &bpf_task_set,
};

static int mymodule_init(void) {
  printk(KERN_ALERT "hello in mymodule_init()\n");
  return register_btf_kfunc_id_set(BPF_PROG_TYPE_UNSPEC, &bpf_task_kfunc_set);
  // return register_btf_kfunc_id_set(BPF_PROG_TYPE_TRACING, &bpf_task_kfunc_set);
}

static void mymodule_exit(void) { 
  printk(KERN_INFO "Goodbye world 1.\n");
}

module_init(mymodule_init);
module_exit(mymodule_exit);
