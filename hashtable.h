#ifndef HASHTABLE_H
#define HASHTABLE_H


#include <iostream>
using namespace std;

template <class T>
class HashTable;


template <class T>
class HashTable{
public:
	HashTable();
	HashTable(int size);
	HashTable(const HashTable<T>& n);
	HashTable& operator =(const HashTable<T>& rhs);
    void showFill();
	~HashTable();
private:
	T * table;
    int tableSize;
};

#include "hashtable.cpp"
#endif //HASHTABLE_H
