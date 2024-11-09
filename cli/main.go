package main

import (
	"fmt"
	"time"

	"github.com/cilium/ebpf/link"
)

//go:generate go run github.com/cilium/ebpf/cmd/bpf2go -cc $BPF_CLANG -cflags $BPF_CFLAGS bpf ./src/main.c -- -I /usr/include/x86_64-linux-gnu -I ./src

func main() {
	fmt.Println("start")
	spec, err := loadBpf()
	if err := spec.RewriteConstants(map[string]interface{}{}); err != nil {
		panic(err)
	}
	fmt.Printf("%v\n", spec)
	fmt.Printf("%v\n", err)
	objs := &bpfObjects{}
	if err := spec.LoadAndAssign(objs, nil); err != nil {
		panic(err)
	}
	fmt.Printf("%v\n", objs)
	fmt.Printf("%v\n", err)
	tracingLink, err := link.AttachTracing(link.TracingOptions{
		Program: objs.bpfPrograms.SysEnter,
	})
	if err != nil {
		panic(err)
	}
	defer tracingLink.Close()

	fmt.Printf("%v\n", tracingLink)
	time.Sleep(1 * time.Second)
}
