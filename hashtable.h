#ifndef HASHTABLE_H
#define HASHTABLE_H

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
	bool insert(T data);
	bool remove(T data);
	bool search(T data) const;
	T howMany() const;
	bool isFull() const;
	bool isEmpty() const;
	void clearTable();
	void pirntTable(ostream& os) const;
	~HashTable();
private:
	T * table;
	int tableSize;
};

#endif //HASHTABLE_H
