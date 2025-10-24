# eBPF Syscall Tracing

## Overview
This project demonstrates how to trace Linux system calls (`open` and `close`) using **eBPF** with **bpftrace**.  
A simple C program is used to generate system calls, and bpftrace measures how frequently they occur.

---

## Requirements
Ensure the following are installed on your Linux system:
- GCC
- bpftrace
- Kernel with eBPF support (Linux 4.9+ recommended)

To install bpftrace (Ubuntu):
```sh
sudo apt update
sudo apt install bpftrace
```

---

## Files Included
| File | Description |
|------|-------------|
| `countSyscalls_Ebpf.c` | C Program that performs multiple open & close operations |

---

## Running the Demo

### Step 1️⃣ — Compile the C Program
```sh
gcc countSyscalls_Ebpf.c -o countSyscalls_Ebpf
```

### Step 2️⃣ — Run bpftrace to Trace Syscalls
```sh
sudo bpftrace -e '
tracepoint:syscalls:sys_enter_openat /comm=="countSyscalls_E"/ { @open_count = count(); }
tracepoint:syscalls:sys_enter_close /comm=="countSyscalls_E"/ { @close_count = count(); }'
```

### Step 3️⃣ — Execute the C Program (in another terminal)
```sh
./countSyscalls_Ebpf
```

You will see output similar to:
```
@[countSyscalls_E, close]: 8
@[countSyscalls_E, open]: 8
```

Each `open()` call is matched by a `close()` call — syscall frequency successfully traced!

---

## Expected Output Breakdown
| Syscall | Expected Count | Notes |
|--------|----------------|------|
| open   | 6              | Based on file loop count |
| close  | 6              | Matches number of open calls |

> NOTE: You may see additional syscalls if traced for **other processes**.  
> This is because system utilities (shell, loader, etc.) can call open/close in the background.

To restrict to only your program, always use the filter:
```
/comm=="syscall_demo"/
```

---

## Key Learning Takeaways
✔ eBPF enables dynamic syscall tracing without modifying kernel code  
✔ bpftrace provides a simple scripting interface for probing  
✔ System call frequency monitoring is useful for performance debugging

---