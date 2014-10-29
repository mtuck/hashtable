template <class T>
class HashTable{
Public:
	HashTable();
	HashTable(T size);
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
Private:
	T table[]; 
};
