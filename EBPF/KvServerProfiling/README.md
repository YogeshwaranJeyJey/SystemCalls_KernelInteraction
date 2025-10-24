# Syscall Profiling of Unix Domain Socket Key-Value Store using `perf`

This document presents the performance profiling results for a Unix Domain Socket (UDS) based Key-Value Store server and client using Linux `perf` tool to trace syscall frequency.

---

## Profiling Commands Used

### Server
```bash
sudo perf stat -e syscalls:sys_enter_read,syscalls:sys_enter_write,syscalls:sys_enter_accept ./uds_server
```

### Client
```bash
sudo perf stat -e syscalls:sys_enter_read,syscalls:sys_enter_write,syscalls:sys_enter_accept ./uds_client
```

---

## Profiling Results

### Server-Side `perf` Output Example

```
 Performance counter stats for './uds_server':

       4      syscalls:sys_enter_read
       6      syscalls:sys_enter_write
       2      syscalls:sys_enter_accept

  36.898671656 seconds time elapsed
```

#### 🔍 Interpretation

| Metric | Meaning | Insights |
|--------|---------|----------|
| `read = 4` | Server read data from the client 4 times | Indicates low client activity |
| `write = 6` | Server responded 6 times | Few commands processed |
| `accept = 2` | Two client connections established | Only one or two sessions active |
| **Time ~36s** | Server mostly idle | Waiting for requests |

---

### Client-Side `perf` Output Example

```
 Performance counter stats for './uds_client':

       7      syscalls:sys_enter_read
       8      syscalls:sys_enter_write
       0      syscalls:sys_enter_accept

  16.986396591 seconds time elapsed
```

#### 🔍 Interpretation

| Metric | Meaning | Insights |
|--------|---------|----------|
| `write = 8` | Client sent 8 commands | Shows request-heavy behavior |
| `read = 7` | Client received server responses | One request might not have a response |
| `accept = 0` | Client does not accept connections | Expected behavior |

---

## Summary of System Behavior

| Observation | Meaning |
|------------|---------|
| Low syscall counts | Indicates light load testing |
| More `write()` than `read()` on client | Client sending commands actively |
| Server waits heavily | Could stress test with multiple commands |

---

## What Can Be Improved?

| Improvement | Benefit |
|------------|----------|
| Increase number of client requests | Better load test server |
| Add multi-client concurrency | Test accept + request throughput |
| Try larger or continuous workload | More realistic server performance insights |

---

## Files in Project

| File | Description |
|------|-------------|
| `uds_server.c` | UDS-based key-value store server |
| `uds_client.c` | Client communicating with server |
| This README | Profiling summary |

---

## 👨‍💻 Author

Yogeshwaran — System Calls & Kernel Interaction Training

---