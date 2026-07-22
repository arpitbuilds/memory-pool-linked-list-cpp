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
