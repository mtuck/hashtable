
class HashTable{
Public:
	HashTable();
	HashTable(int size);
	HashTable(const HashTable& n);
	HashTable& operator =(const HashTable& rhs);
	bool insert(int data);  
	bool remove(int data);
	bool search(int data) const;
	int howMany() const;
	bool isFull() const;
	bool isEmpty() const;
	void clearTable();
	void pirntTable(ostream& os) const;
	~HashTable();
Private:
	int table[]; 
};



