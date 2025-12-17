#ifndef DLL_H
#define DLL_H
#include <iostream>
#include <fstream>
using namespace std;
template <typename T>
class DoublyLinkedList {
private:
    size_t sz = 0;
public:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        Node(T v) : value(v), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    size_t size() const {return sz;}
    DoublyLinkedList();
    ~DoublyLinkedList();

    void addHead(T value);
    void addTail(T value);
    void addBeforeValue(T target, T value);
    void addAfterValue(T target, T value);

    void deleteHead();
    void deleteTail();
    void deleteValue(T value);               
    void deleteBeforeValue(T target);
    void deleteAfterValue(T target);

    bool search(T value) const;
    void readForward() const;
    void readBackward() const;

    void saveToFile(const string& filename = "txt/dll.txt") const;
    void loadFromFile(const string& filename = "txt/dll.txt");

    bool isEmpty() const { return head == nullptr; }
    void clear();
    int length() const;
};
#include "../dll.tpp"
#endif
