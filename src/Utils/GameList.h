#ifndef GAMELIST_H
#define GAMELIST_H

template <typename T>
class GameList {
private:
    T* data;
    int capacity;
    int size;
    
    void resize();

public:
    GameList();
    ~GameList();
    
    void add(const T& element);
    void remove(int index);  
    T& get(int index);
    int getSize() const;
    void clear();
};

#include "GameList.tpp"

#endif
