#include <linux/types.h>
#include <bpf/bpf_helpers.h>
#include <bpf/bpf_tracing.h>
#include <linux/bpf.h>

extern int bpf_hello(int id__k) __ksym;
extern int bpf_hello_const(int id) __ksym;

SEC("tp_btf/sys_enter")
int BPF_PROG(sys_enter, struct pt_regs *regs, long syscall_id)
{
    char fmt[] = "do_sys_clone";
    bpf_trace_printk(fmt, sizeof(fmt));
    bpf_hello(syscall_id);
    bpf_hello_const(200);
    return 0;
}

char __license[] SEC("license") = "Dual MIT/GPL";
