#ifndef ARRAY_H
#define ARRAY_H
#include <iostream>
#include <initializer_list>
#include <fstream>
#include <sstream>

using namespace std;

template<typename T>
class Array {
private:
   T* data;

public:
   size_t size;
   size_t capacity;
   
   Array(size_t cap);
   Array(const Array& arr);
   Array(initializer_list<T> list);

   void addEnd(Array& arr, size_t index, const T& value); 
   void arrayAddEnd(Array& arr, const T& value);
   void arrayAddIndex(Array& arr, size_t index, const T& value);
   
   T arrayGet(Array& arr, size_t index);
   void arraySet(Array& arr, size_t index, const T& value);
   
   void arrayDeleteIndex(Array& arr, size_t index);
   void arrayDeleteEnd(Array& arr);
   
   int arrayLength(Array& arr);
   void arrayRead(Array& arr);
   void saveToFile();
   void loadFromFile();
   ~Array();
};

#include "../array.tpp"

#endif