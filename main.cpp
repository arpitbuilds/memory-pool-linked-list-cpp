#include <iostream>

// The Node structure used in the Linked List
struct Node {
    int data;
    Node* next;
};

// Global pointers to manage the lists
Node* activeHead = nullptr; // Head of the active elements list
Node* freeHead = nullptr;   // Head of the recycled nodes list (Node Pool)

/**
 * Memory Allocation Algorithm: getNode
 * Checks the Free List (Node Pool) first. If a recycled node is available,
 * it pulls it from the pool. Otherwise, it allocates a new node on the heap.
 */
Node* getNode(int value) {
    if (freeHead != nullptr) {
        // Recycle node from the pool (Zero heap allocation overhead)
        Node* temp = freeHead;
        freeHead = freeHead->next; // Move head to next free node
        
        temp->data = value;
        temp->next = nullptr;
        std::cout << "[Recycled Node] Reusing heap memory block for value: " << value << "\n";
        return temp;
    } else {
        // No recycled nodes available; perform a standard heap allocation
        Node* temp = new Node();
        temp->data = value;
        temp->next = nullptr;
        std::cout << "[Allocated Node] Created new heap memory block for value: " << value << "\n";
        return temp;
    }
}

/**
 * Insertion Algorithm: insertAtFront
 * Prepends a node containing the specified value to the active list.
 */
void insertAtFront(int value) {
    Node* temp = getNode(value);
    temp->next = activeHead;
    activeHead = temp;
    std::cout << "[Inserted] " << value << " added to the active list.\n";
}

/**
 * Deletion & Memory Optimization Algorithm: deleteFromFront
 * Removes the front node from the active list and moves it to the Free List.
 * This bypasses the standard 'delete' call, recycling the node for future use.
 */
void deleteFromFront() {
    if (activeHead == nullptr) {
        std::cout << "[Delete Warning] Active list is empty. Nothing to delete.\n";
        return;
    }

    Node* temp = activeHead;
    activeHead = activeHead->next;

    // Memory Optimization: instead of calling 'delete temp', push it to the Free List pool
    temp->next = freeHead;
    freeHead = temp;
    std::cout << "[Deactivated] Node containing " << temp->data << " moved to the Free List pool.\n";
}

/**
 * Display Helper: printActiveList
 * Outputs the values currently in the active list.
 */
void printActiveList() {
    std::cout << "Active List: ";
    Node* current = activeHead;
    if (current == nullptr) {
        std::cout << "(empty)";
    }
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "NULL\n";
}

/**
 * Display Helper: printFreeList
 * Outputs the values currently residing in the recycled node pool.
 */
void printFreeList() {
    std::cout << "Free List Pool: ";
    Node* current = freeHead;
    if (current == nullptr) {
        std::cout << "(empty)";
    }
    while (current != nullptr) {
        std::cout << "[" << current->data << "] -> ";
        current = current->next;
    }
    std::cout << "NULL\n";
}

/**
 * Memory Safety Algorithm: freeAllMemory
 * Traverses both the active list and the free list to deallocate all heap nodes,
 * ensuring zero memory leaks when the program terminates.
 */
void freeAllMemory() {
    std::cout << "\n--- Starting Complete Memory Cleanup ---\n";
    
    int activeFreed = 0;
    int poolFreed = 0;

    // 1. Free all nodes in the active list
    while (activeHead != nullptr) {
        Node* temp = activeHead;
        activeHead = activeHead->next;
        delete temp;
        activeFreed++;
    }

    // 2. Free all nodes in the free list (pool)
    while (freeHead != nullptr) {
        Node* temp = freeHead;
        freeHead = freeHead->next;
        delete temp;
        poolFreed++;
    }

    std::cout << "[Memory Safety] Freed " << activeFreed << " active nodes and " 
              << poolFreed << " pool nodes.\n";
    std::cout << "[Memory Safety] Memory leak check: SUCCESS. All allocations cleared.\n";
}

int main() {
    std::cout << "====================================================\n";
    std::cout << "Memory-Recycled Linked List Demonstration\n";
    std::cout << "====================================================\n\n";

    // 1. Insert values (forces new dynamic allocations)
    std::cout << "--- Step 1: Populating list ---\n";
    insertAtFront(10);
    insertAtFront(20);
    insertAtFront(30);
    printActiveList();
    printFreeList();
    std::cout << "\n";

    // 2. Delete values (recycles node memory instead of destroying them)
    std::cout << "--- Step 2: Deleting elements (Recycling memory) ---\n";
    deleteFromFront();
    deleteFromFront();
    printActiveList();
    printFreeList();
    std::cout << "\n";

    // 3. Insert new values (should trigger node reuse)
    std::cout << "--- Step 3: Inserting new elements (Reusing recycled nodes) ---\n";
    insertAtFront(40); // Will reuse the node that previously held 20
    insertAtFront(50); // Will reuse the node that previously held 30
    printActiveList();
    printFreeList();
    std::cout << "\n";

    // 4. Clean up all memory to prevent leaks
    freeAllMemory();

    return 0;
}
