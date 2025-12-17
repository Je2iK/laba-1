#include "./include/queue.h"
template <typename T>
void Queue<T>::create(int cap) {
    if (cap <= 0) {
        std::cerr << "Capacity must be positive.\n";
        return;
    }
    delete[] data;
    data = new T[cap];
    capacity = cap;
    head = tail = size = 0;
}

template <typename T>
bool Queue<T>::push(const T& value) {
    if (isFull()) {
        int newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[newCapacity];
        int current = head;
        for (int i = 0; i < size; ++i) {
            newData[i] = data[current];
            current = (current + 1) % capacity;
        }
        delete[] data;
        data = newData;
        head = 0;
        tail = size;
        capacity = newCapacity;
    }
    data[tail] = value;
    tail = (tail + 1) % capacity;
    ++size;
    return true;
}

template <typename T>
T Queue<T>::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty.");
    }
    T value = data[head];
    head = (head + 1) % capacity;
    --size;
    return value;
}

template <typename T>
void Queue<T>::read() const {
    if (isEmpty()) {
        std::cout << "Queue is empty.\n";
        return;
    }
    std::cout << "Queue: ";
    int i = head;
    for (int j = 0; j < size; ++j) {
        std::cout << data[i] << " ";
        i = (i + 1) % capacity;
    }
    std::cout << "\n";
}

template <typename T>
void Queue<T>::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file for writing: " << filename << "\n";
        return;
    }
    int i = head;
    for (int j = 0; j < size; ++j) {
        file << data[i] << "\n";
        i = (i + 1) % capacity;
    }
    file.close();
}

template <typename T>
void Queue<T>::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file for reading: " << filename << "\n";
        return;
    }

    delete[] data;
    data = nullptr;
    head = tail = size = 0;

    T value;
    int count = 0;
    while (file >> value) {
        ++count;
    }
    file.clear();
    file.seekg(0);

    if (count == 0) {
        capacity = 1; 
        create(1);
        return;
    }

    create(count);
    while (file >> value) {
        push(value);
    }
    file.close();
}
