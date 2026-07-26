# Memory-Recycled Linked List

A memory-optimized singly linked list in C++ that uses a custom **free list** (node pool) to recycle deleted nodes, bypassing repeated OS heap allocations.

## Features

- **Node Recycling:** Deleted nodes are pushed to a free list rather than deallocated.
- **$O(1)$ Operations:** Constant-time node allocation and recycling.
- **Leak-Free:** Explicit cleanup of active and recycled nodes on termination.

## How to Run

Compile and execute the program:

```bash
g++ main.cpp -o main
./main
```

