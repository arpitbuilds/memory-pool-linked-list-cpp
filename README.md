# Memory-Recycled Linked List in C++

A simple, academic-style DSA project designed to demonstrate **low-level memory optimization** and **preventing memory leaks** using C++.

## 🚀 Key Interview Topics & Keywords Covered

* **Data Structure:** Singly Linked List (Nodes linked via pointers).
* **Algorithm:** Node recycling (checking the free list first), node insertion, and recursive/iterative list traversal.
* **Memory Optimization:** Custom memory recycling (Node Pool/Free List) to bypass constant OS allocations (`new` and `delete`) and avoid heap fragmentation.
* **Memory Leak Prevention:** Deallocating both active and recycled nodes during termination (monitored and verified via Valgrind).
* **Platform Independent:** Written in ISO standard C++ with standard input/output streams, making it executable on Windows, Linux, and macOS.
* **Complexity Analysis:** Node allocation/recycling is $O(1)$ constant time, list insertion is $O(1)$ constant time, and final cleanup is $O(N)$ linear time.

---

## 🛠️ How to Compile and Run

### On Windows (using g++ or MSVC cl):
```bash
# Open cmd/powershell in this folder:
g++ main.cpp -o main.exe
./main.exe
```

### On Linux / macOS:
```bash
g++ main.cpp -o main
./main
```

---

## 🔍 How to Check for Memory Leaks (using Valgrind)

In the interview, the recruiter will ask how you verified that your code doesn't leak memory. Explain that you used **Valgrind**:

1. Compile the code with debugging symbols (`-g`):
   ```bash
   g++ -g main.cpp -o main
   ```
2. Run Valgrind:
   ```bash
   valgrind --leak-check=full ./main
   ```
3. Look at the output. It should say:
   `All heap blocks were freed -- no leaks are possible`.

---

## 💡 Quick Interview Q&A Cheatsheet (Read this before the interview!)

### Q1: Why is this project "memory optimized"?
**Answer:** Standard linked lists call `new` (allocation) every time an item is added, and `delete` (deallocation) every time an item is removed. This causes heap fragmentation and slows down performance. My project intercepts deletion and stores the node in a `freeHead` pool. When we need a new node, we reuse it, bypassing the OS memory manager completely.

### Q2: What is the complexity of your custom allocator?
**Answer:** It is $O(1)$ constant time. Since the recycled nodes are linked together, pushing a node to the free pool or popping a node from the free pool is just a pointer reassignment.

### Q3: How did you ensure there are no memory leaks?
**Answer:** Since deleted nodes are not freed immediately (they are stored in the pool), we must make sure to clear both the active list AND the free pool when the program terminates. The function `freeAllMemory()` traverses both lists and deletes every remaining node.
