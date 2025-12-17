#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class Stack {
private:
    T* data;
    int top;
    int capacity;

public:
    Stack() : data(nullptr), top(-1), capacity(0) {}
    
    ~Stack() {
        delete[] data;
    }

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void create(int cap);
    bool push(const T& value);
    T pop();
    void read() const;
    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == capacity - 1; }

    void saveToFile(const std::string& filename = "txt/stack.txt") const;
    void loadFromFile(const std::string& filename = "txt/stack.txt");
};
#include "../stack.tpp"
#endif