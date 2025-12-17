#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "include/array.h"

template<typename T>
Array<T>::Array(size_t cap) : data(new T[cap]), size(0), capacity(cap) {}

template<typename T>
Array<T>::Array(const Array& arr) : data(new T[arr.size]), size(arr.size), capacity(arr.capacity) {
    for(size_t i = 0; i < size; ++i) 
        data[i] = arr.data[i];
}

template<typename T>
Array<T>::Array(initializer_list<T> list) : data(new T[list.size()]), size(list.size()), capacity(list.size()) {
    size_t i = 0;
    for(const T& item : list) {
        data[i++] = item;
    }
}

template<typename T>
Array<T>::~Array() {
    delete[] data;
}

template<typename T>
void Array<T>::saveToFile() {
    ofstream file("txt/array.txt");
    if(!file.is_open()) {
        cerr << "Не удалось открыть файл для записи: " << "array.txt" << endl;
        return;
    }

    file << size << "\n";
    for(size_t i = 0; i < size; ++i) {
        file << data[i] << "\n";
    }

    file.close();
    cout << "Массив успешно сохранён в " << "array.txt" << endl;
}

template<typename T>
void Array<T>::loadFromFile() {
    ifstream file("txt/array.txt");
    if(!file.is_open()) {
        cerr << "Не удалось открыть файл для чтения: " << "array.txt" << endl;
        return;
    }

    size_t newSize;
    if (!(file >> newSize)) {
        cerr << "Ошибка чтения размера массива!" << endl;
        return;
    }
    
    delete[] data;
    data = new T[newSize];
    size = newSize;
    capacity = newSize;

    for(size_t i = 0; i < newSize; ++i) {
        if (!(file >> data[i])) { 
            cerr << "Ошибка чтения элемента " << i << endl;
            size = i;
            break;
        }
    }

    file.close();
    cout << "Массив успешно загружен из " << "array.txt" << endl;
}

template<typename T>
void Array<T>::arrayAddEnd(Array& arr, const T& value) {
    if (arr.size >= arr.capacity) {
        size_t newCapacity = arr.capacity == 0 ? 1 : arr.capacity * 2;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < arr.size; i++)
            newData[i] = arr.data[i];
        delete[] arr.data;
        arr.data = newData;
        arr.capacity = newCapacity;
    }
    arr.data[arr.size++] = value;
}

template<typename T>
void Array<T>::arrayAddIndex(Array& arr, size_t index, const T& value) {
    if (arr.capacity == 0) {
        arr.capacity = 1;
        arr.data = new T[arr.capacity];
    }
    else if (arr.size >= arr.capacity) {
        arr.capacity *= 2;
        T* newData = new T[arr.capacity];
        for (size_t i = 0; i < arr.size; i++)
            newData[i] = arr.data[i];
        delete[] arr.data;
        arr.data = newData;
    }

    if (index <= arr.size) {
        for (size_t i = arr.size; i > index; i--)
            arr.data[i] = arr.data[i - 1];
        arr.data[index] = value;
        arr.size++;
    }
}

template<typename T>
void Array<T>::arrayDeleteEnd(Array& arr) {
    if (arr.size > 0) {
        arr.size--;
    }
}

template<typename T>
T Array<T>::arrayGet(Array& arr, size_t index) {
    if (index < arr.size) {
        return arr.data[index];
    } else {
        return T(); 
    }
}

template<typename T>
void Array<T>::arraySet(Array& arr, size_t index, const T& value) {
    if (index < arr.size)
        arr.data[index] = value;
}

template<typename T>
void Array<T>::arrayDeleteIndex(Array& arr, size_t index) {
    if (index < arr.size) {
        for (size_t i = index; i < arr.size - 1; i++)
            arr.data[i] = arr.data[i+1];
        arr.size--;
    }
}

template<typename T>
int Array<T>::arrayLength(Array& arr) {
    return arr.size;
}

template<typename T>
void Array<T>::arrayRead(Array& arr) {
    for (size_t i = 0; i < arr.size; i++)
        cout << arr.data[i] << " ";
    cout << endl;
}

#endif
