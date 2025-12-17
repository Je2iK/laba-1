#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class Queue {
private:
    T* data;
    int head, tail, size, capacity;

public:
    Queue() : data(nullptr), head(0), tail(0), size(0), capacity(0) {}
    
    ~Queue() {
        delete[] data;
    }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void create(int cap);
    bool push(const T& value);
    T pop();
    void read() const;
    bool isEmpty() const { return size == 0; }
    bool isFull() const { return size == capacity; }

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};
#include "../queue.tpp"
#endif