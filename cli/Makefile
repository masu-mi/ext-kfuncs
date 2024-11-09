CLANG ?= clang
CFLAGS := -O2 -g -Wall -Werror $(CFLAGS)
DEST ?= out

.PHONY: help
help:

.PHONY: bpf-gen
bpf-gen: export BPF_CLANG := $(CLANG)
bpf-gen: export BPF_CFLAGS := $(CFLAGS) $(CEXTRA_FLAGS)
bpf-gen: ## generate ebpf code and object files
	docker build --progress plain --build-arg BPF_CLANG=${BPF_CLANG} \
		--build-arg BPF_CFLAGS="${BPF_CFLAGS}" . --output ./ -f Dockerfile.bpf

.PHONY: load-bpf
load-bpf: ## load bpf program
	bpftool prog load ./bpf_bpfel.o /sys/fs/bpf/hello

build: ## build go program
	go build -o $(DEST)/

help: ## Show this help.
	@echo ''
	@echo 'Usage:'
	@echo '  ${YELLOW}make${RESET} ${GREEN}<target>${RESET}'
	@echo ''
	@echo 'Targets:'
	@awk 'BEGIN {FS = ":.*?## "} { \
		if (/^[a-zA-Z_-]+:.*?##.*$$/) { \
			printf "    ${YELLOW}%-30s${GREEN}%s${RESET}\n", $$1, $$2 \
		} \
		else if (/^## .*$$/) {printf "  ${CYAN}%s${RESET}\n", substr($$1,4)} \
		}' $(MAKEFILE_LIST)
