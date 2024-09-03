#pragma once
#include <iostream>
#include <stdexcept>
#include"DataSource.hpp"
const size_t SIZE = 4;
const size_t DEFAULT_CAPACITY = 10;

template <typename T>
class Vector {
public:
    Vector();
    Vector(size_t size);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    ~Vector();
public:
    T& at(size_t position);
    void push_back(const T& element);
    void pop_back();
    void print(std::ostream& out) const;
    const T* getData()const;
    size_t getSize() const;
    bool isEmpty()const;
    void reserve(size_t newCapacity);
    
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void clean();
   
   
private:
   
    void copy(const Vector& other);
    void expand();

private:
    T* arr;
    size_t size;
    size_t capacity;

};

template <typename T>
Vector<T>::Vector() : arr(nullptr), size(0), capacity(0) {}

template<typename T>
inline Vector<T>::Vector(size_t size) : size(size), capacity(size), arr(nullptr)
{
    try {
        if (size > 0) {
            arr = new T[size];
        }
    }
    catch (const std::bad_alloc& e) {
        throw std::runtime_error("Failed to allocate memory");
    }
}

template <typename T>
Vector<T>::Vector(const Vector& other) {
    copy(other);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        clean();
        copy(other);
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector() {
    clean();
}

template <typename T>
T& Vector<T>::at(size_t position) {
    if (position >= size) {
        throw std::out_of_range("Vector.at: Out of range");
    }
    return arr[position];
}

template <typename T>
void Vector<T>::push_back(const T& element) {
    if (arr == nullptr)
        arr = new T[SIZE];
    if (size >= capacity)
        expand();
    arr[this->size] = element;
    this->size++;
}

template <typename T>
void Vector<T>::pop_back() {
    if (size == 0) {
        throw std::out_of_range("Vector.pop_back: No element to pop!");
    }
    this->size--;
}

template <typename T>
void Vector<T>::print(std::ostream& out) const {
    for (size_t i = 0; i < size; ++i) {
        out << arr[i] << " ";
    }
    out << std::endl;
}
template<typename T>
inline const T* Vector<T>::getData() const
{
    return arr;
}

template <typename T>
size_t Vector<T>::getSize() const {
    return size;
}
template<typename T>
bool Vector<T>::isEmpty()const {
    return size == 0;
}
template<typename T>
void Vector<T>::reserve(size_t newCapacity) {

    if (newCapacity > capacity) {
        T* newArray = new T[newCapacity]; 
        for (size_t i = 0; i < size; ++i) {
            newArray[i] = arr[i]; 
        }
        delete[] arr; 
        arr = newArray; 
        capacity = newCapacity; 
    }
}

template <typename T>
T& Vector<T>::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template <typename T>
void Vector<T>::clean() {
    delete[] arr;
    arr = nullptr;
    size = 0;
    capacity = 0;
}

template <typename T>
void Vector<T>::copy(const Vector& other) {
    if (other.size > other.capacity) {
        throw std::runtime_error("Size exceeds capacity in the source vector.");
    }
    arr = new T[other.capacity];
    for (size_t i = 0; i < other.size; ++i) {
        arr[i] = other.arr[i];
    }
    size = other.size;
    capacity = other.capacity;
}

template <typename T>
void Vector<T>::expand() {
    if (capacity == 0) {
        reserve(DEFAULT_CAPACITY); 
    }
    else {
        reserve(capacity * 2); 
    }
}

