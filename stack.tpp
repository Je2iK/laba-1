#include "./include/stack.h"
#include <fstream>
template <typename T>
void Stack<T>::create(int cap) {
    if (cap <= 0) {
        std::cerr << "Capacity must be positive.\n";
        return;
    }
    delete[] data;
    data = new T[cap];
    capacity = cap;
    top = -1;
}

template <typename T>
bool Stack<T>::push(const T& value) {
    if (isFull()) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[newCapacity];
        for (int i = 0; i <= top; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
    data[++top] = value;
    return true;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack underflow.");
    }
    return data[top--];
}

template <typename T>
void Stack<T>::read() const {
    if (isEmpty()) {
        std::cout << "Stack is empty.\n";
        return;
    }
    std::cout << "Stack (top to bottom): ";
    for (int i = top; i >= 0; --i) {
        std::cout << data[i] << " ";
    }
    std::cout << "\n";
}

template <typename T>
void Stack<T>::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file for writing: " << filename << "\n";
        return;
    }
    for (int i = top; i >= 0; --i) {
        file << data[i] << "\n";
    }
    file.close();
}

template <typename T>
void Stack<T>::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file for reading: " << filename << "\n";
        return;
    }

    delete[] data;
    data = nullptr;
    top = -1;
    capacity = 0;

    T value;
    int count = 0;
    while (file >> value) {
        ++count;
    }
    file.clear();
    file.seekg(0);

    if (count == 0) {
        create(1);
        return;
    }

    create(count);
    T* temp = new T[count];
    for (int i = 0; i < count && file >> temp[i]; ++i) {}

    for (int i = count - 1; i >= 0; --i) {
        push(temp[i]);
    }

    delete[] temp;
    file.close();
}

