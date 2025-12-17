#include "./include/dll.h"

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
}

template <typename T>
int DoublyLinkedList<T>::length() const {
    int count = 0;
    Node* cur = head;
    while (cur) { count++; cur = cur->next; }
    return count;
}


template <typename T>
void DoublyLinkedList<T>::addHead(T value) {
    Node* node = new Node(value);
    node->next = head;
    if (head) head->prev = node;
    head = node;
    if (!tail) tail = node;
}

template <typename T>
void DoublyLinkedList<T>::addTail(T value) {
    Node* node = new Node(value);
    node->prev = tail;
    if (tail) tail->next = node;
    tail = node;
    if (!head) head = node;
    ++sz;
}

template <typename T>
void DoublyLinkedList<T>::addBeforeValue(T target, T value) {
    Node* cur = head;
    while (cur && cur->value != target) cur = cur->next;
    if (!cur) return;

    Node* node = new Node(value);
    node->next = cur;
    node->prev = cur->prev;

    if (cur->prev) cur->prev->next = node;
    else head = node;

    cur->prev = node;
}

template <typename T>
void DoublyLinkedList<T>::addAfterValue(T target, T value) {
    Node* cur = head;
    while (cur && cur->value != target) cur = cur->next;
    if (!cur) return;

    Node* node = new Node(value);
    node->prev = cur;
    node->next = cur->next;

    if (cur->next) cur->next->prev = node;
    else tail = node;

    cur->next = node;
}

template <typename T>
void DoublyLinkedList<T>::deleteHead() {
    if (!head) return;
    Node* temp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete temp;
}

template <typename T>
void DoublyLinkedList<T>::deleteTail() {
    if (!tail) return;
    Node* temp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete temp;
}

template <typename T>
void DoublyLinkedList<T>::deleteValue(T value) {
    Node* cur = head;
    while (cur && cur->value != value) cur = cur->next;
    if (!cur) return;

    if (cur->prev) cur->prev->next = cur->next;
    else head = cur->next;

    if (cur->next) cur->next->prev = cur->prev;
    else tail = cur->prev;

    delete cur;
}

template <typename T>
void DoublyLinkedList<T>::deleteBeforeValue(T target) {
    Node* cur = head;
    while (cur && cur->value != target) cur = cur->next;
    if (!cur || !cur->prev) return;
    deleteValue(cur->prev->value);
}

template <typename T>
void DoublyLinkedList<T>::deleteAfterValue(T target) {
    Node* cur = head;
    while (cur && cur->value != target) cur = cur->next;
    if (!cur || !cur->next) return;
    deleteValue(cur->next->value);
}


template <typename T>
bool DoublyLinkedList<T>::search(T value) const {
    Node* cur = head;
    while (cur) {
        if (cur->value == value) return true;
        cur = cur->next;
    }
    return false;
}

template <typename T>
void DoublyLinkedList<T>::readForward() const {
    Node* cur = head;
    while (cur) { cout << cur->value << " "; cur = cur->next; }
    cout << endl;
}
template <typename T>
void DoublyLinkedList<T>::readBackward() const {
    Node* cur = tail;
    while (cur) { cout << cur->value << " "; cur = cur->prev; }
    cout << endl;
}



template <typename T>
void DoublyLinkedList<T>::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) { cerr << "Ошибка открытия файла: " << filename << endl; return; }

    file << length() << "\n";
    Node* cur = head;
    while (cur) { file << cur->value << "\n"; cur = cur->next; }

    file.close();
}

template <typename T>
void DoublyLinkedList<T>::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) { cerr << "Ошибка открытия файла: " << filename << endl; return; }

    clear();

    int n;
    T value;
    file >> n;
    for (int i = 0; i < n; ++i) {
        file >> value;
        addTail(value);
    }

    file.close();
}
