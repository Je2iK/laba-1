#ifndef SLL_H
#define SLL_H

#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class SinglyLinkedList {
public:
    struct Node {
        T value;
        Node* next;
        Node(const T& v) : value(v), next(nullptr) {}
    };

    Node* head; // указатель на первый элемент

    // Конструктор
    SinglyLinkedList() : head(nullptr) {}

    // Деструктор
    ~SinglyLinkedList() {
        clear();
    }

    // Запрет копирования (если не реализованы — лучше запретить, чтобы избежать двойного удаления)
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;

    // Очистка списка
    void clear() {
        Node* cur = head;
        while (cur) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head = nullptr;
    }

    // Методы добавления
    void addHead(const T& value);
    void addTail(const T& value);
    void addBefore(const T& target, const T& value);
    void addAfter(const T& target, const T& value);

    // Методы удаления
    void deleteHead();
    void deleteTail();
    void deleteValue(const T& value);
    void deleteBefore(const T& target);
    void deleteAfter(const T& target);

    // Прочие операции
    bool search(const T& value) const;
    void read() const; // вывод списка
    void saveToFile(const std::string& filename = "txt/sll.txt") const;
    void loadFromFile(const std::string& filename = "txt/sll.txt");

    // Вспомогательное
    bool isEmpty() const { return head == nullptr; }
};
#include "../sll.tpp"
#endif 