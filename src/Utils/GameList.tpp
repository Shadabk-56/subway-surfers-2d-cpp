#ifndef GAMELIST_TPP
#define GAMELIST_TPP

#include <iostream>

template <typename T>
GameList<T>::GameList() : capacity(10), size(0) {
    data = new T[capacity];
}

template <typename T>
GameList<T>::~GameList() {
    delete[] data;
}

template <typename T>
void GameList<T>::add(const T& element) {
    if (size >= capacity) {
        resize();
    }
    data[size++] = element;
}

// REMOVE FUNCTION
template <typename T>
void GameList<T>::remove(int index) {
    if (index < 0 || index >= size) {
        std::cout << "Error: Index out of bounds in GameList::remove()" << std::endl;
        return;
    }
    
    // Shift elements to the left
    for (int i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

template <typename T>
void GameList<T>::resize() {
    capacity *= 2;
    T* newData = new T[capacity];
    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

template <typename T>
T& GameList<T>::get(int index) {
    if (index < 0 || index >= size) {
        std::cout << "Error: Index out of bounds in GameList::get()" << std::endl;
        // Return first element as fallback
        return data[0];
    }
    return data[index];
}

template <typename T>
int GameList<T>::getSize() const {
    return size;
}

template <typename T>
void GameList<T>::clear() {
    size = 0;
}

#endif
