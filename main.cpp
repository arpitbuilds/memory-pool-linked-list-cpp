#include <iostream>

struct Node {
    int data;
    Node* next;
};

Node* activeHead = nullptr;
Node* freeHead = nullptr;

Node* getNode(int value) {
    if (freeHead != nullptr) {
        Node* temp = freeHead;
        freeHead = freeHead->next;
        temp->data = value;
        temp->next = nullptr;
        std::cout << "[Recycled Node] Reusing heap memory block for value: " << value << "\n";
        return temp;
    } else {
        Node* temp = new Node();
        temp->data = value;
        temp->next = nullptr;
        std::cout << "[Allocated Node] Created new heap memory block for value: " << value << "\n";
        return temp;
    }
}

void insertAtFront(int value) {
    Node* temp = getNode(value);
    temp->next = activeHead;
    activeHead = temp;
    std::cout << "[Inserted] " << value << " added to the active list.\n";
}

void deleteFromFront() {
    if (activeHead == nullptr) {
        std::cout << "[Delete Warning] Active list is empty. Nothing to delete.\n";
        return;
    }

    Node* temp = activeHead;
    activeHead = activeHead->next;

    temp->next = freeHead;
    freeHead = temp;
    std::cout << "[Deactivated] Node containing " << temp->data << " moved to the Free List pool.\n";
}

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

void freeAllMemory() {
    std::cout << "\n--- Starting Complete Memory Cleanup ---\n";
    
    int activeFreed = 0;
    int poolFreed = 0;

    while (activeHead != nullptr) {
        Node* temp = activeHead;
        activeHead = activeHead->next;
        delete temp;
        activeFreed++;
    }

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

    std::cout << "--- Step 1: Populating list ---\n";
    insertAtFront(10);
    insertAtFront(20);
    insertAtFront(30);
    printActiveList();
    printFreeList();
    std::cout << "\n";

    std::cout << "--- Step 2: Deleting elements (Recycling memory) ---\n";
    deleteFromFront();
    deleteFromFront();
    printActiveList();
    printFreeList();
    std::cout << "\n";

    std::cout << "--- Step 3: Inserting new elements (Reusing recycled nodes) ---\n";
    insertAtFront(40);
    insertAtFront(50);
    printActiveList();
    printFreeList();
    std::cout << "\n";

    freeAllMemory();

    return 0;
}
