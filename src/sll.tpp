#include "./include/sll.h"
template <typename T>
void SinglyLinkedList<T>::addHead(const T& value) {
    Node* newNode = new Node(value);
    newNode->next = head;
    head = newNode;
}

template <typename T>
void SinglyLinkedList<T>::addTail(const T& value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        return;
    }
    Node* cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = newNode;
}

template <typename T>
void SinglyLinkedList<T>::addBefore(const T& target, const T& value) {
    if (!head) return;

    if (head->value == target) {
        addHead(value);
        return;
    }

    Node* cur = head;
    while (cur->next && cur->next->value != target) {
        cur = cur->next;
    }

    if (cur->next) {
        Node* newNode = new Node(value);
        newNode->next = cur->next;
        cur->next = newNode;
    } else {
        std::cerr << "Target not found for addBefore.\n";
    }
}

template <typename T>
void SinglyLinkedList<T>::addAfter(const T& target, const T& value) {
    Node* cur = head;
    while (cur && cur->value != target) {
        cur = cur->next;
    }

    if (!cur) {
        std::cerr << "Target not found for addAfter.\n";
        return;
    }

    Node* newNode = new Node(value);
    newNode->next = cur->next;
    cur->next = newNode;
}

template <typename T>
void SinglyLinkedList<T>::deleteHead() {
    if (!head) return;
    Node* temp = head;
    head = head->next;
    delete temp;
}

template <typename T>
void SinglyLinkedList<T>::deleteTail() {
    if (!head) return;
    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }
    Node* cur = head;
    while (cur->next->next) {
        cur = cur->next;
    }
    delete cur->next;
    cur->next = nullptr;
}

template <typename T>
void SinglyLinkedList<T>::deleteValue(const T& value) {
    if (!head) return;

    if (head->value == value) {
        deleteHead();
        return;
    }

    Node* cur = head;
    while (cur->next && cur->next->value != value) {
        cur = cur->next;
    }

    if (cur->next) {
        Node* toDelete = cur->next;
        cur->next = toDelete->next;
        delete toDelete;
    }
}

template <typename T>
void SinglyLinkedList<T>::deleteAfter(const T& target) {
    Node* cur = head;
    while (cur && cur->value != target) {
        cur = cur->next;
    }

    if (!cur || !cur->next) {
        std::cerr << "No node after target to delete.\n";
        return;
    }

    Node* toDelete = cur->next;
    cur->next = toDelete->next;
    delete toDelete;
}

template <typename T>
void SinglyLinkedList<T>::deleteBefore(const T& target) {
    if (!head || !head->next) return;

    if (head->next->value == target) {
        deleteHead();
        return;
    }

    Node* cur = head;
    while (cur->next->next && cur->next->next->value != target) {
        cur = cur->next;
    }

    if (cur->next->next) {
        Node* toDelete = cur->next;
        cur->next = toDelete->next;
        delete toDelete;
    } else {
        std::cerr << "No node before target found.\n";
    }
}

template <typename T>
bool SinglyLinkedList<T>::search(const T& value) const {
    Node* cur = head;
    while (cur) {
        if (cur->value == value) return true;
        cur = cur->next;
    }
    return false;
}

template <typename T>
void SinglyLinkedList<T>::read() const {
    if (!head) {
        std::cout << "List is empty.\n";
        return;
    }
    Node* cur = head;
    while (cur) {
        std::cout << cur->value << " -> ";
        cur = cur->next;
    }
    std::cout << "nullptr\n";
}

template <typename T>
void SinglyLinkedList<T>::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file for writing: " << filename << "\n";
        return;
    }

    Node* cur = head;
    while (cur) {
        file << cur->value << "\n";
        cur = cur->next;
    }
    file.close();
}

template <typename T>
void SinglyLinkedList<T>::loadFromFile(const std::string& filename) {
    clear();

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file for reading: " << filename << "\n";
        return;
    }

    T value;
    while (file >> value) {
        addTail(value);
    }
    file.close();
}

