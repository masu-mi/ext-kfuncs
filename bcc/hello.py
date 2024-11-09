#!/usr/bin/env python3

from bcc import BPF

program = r"""

extern u32 bpf_hello(u32 pid);

int hello(void *ctx) {
    bpf_trace_printk("Hello, World!");
    bpf_trace_printk(":wey:");
    bpf_hello(1);
    return 0;
}
"""

b = BPF(text=program)
syscall = b.get_syscall_fnname("clone")
b.attach_kprobe(event=syscall, fn_name="hello")

b.trace_print()
