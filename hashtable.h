//=============================================================================
//CS355 Assignment #2
//Martin Tuck, Victor Rogers, Tyler Yasaka
//Documentation, current & previous project version can be found on Github:
//https://github.com/mtuck/hashtable
//=============================================================================

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <fstream>
#include <cmath>

using namespace std;
const int NUMOFPRIMES = 10000;  
const int MAXTABLESIZE = 104729;   //max number of key the constructor will take is MAXTABLESIZE/2

int findClosestPrime(int size);

template <class T>
class HashTable;


//=============================================================================
//Class: HashTable
//=============================================================================
template <class T>
class HashTable{
public:
	HashTable();
	HashTable(int size);
	HashTable(const HashTable<T>& n);
	HashTable& operator =(const HashTable<T>& rhs);
	~HashTable();
	
	int Insert(T key);
	int Remove(T key);
	void ClearTable();
	
	int Search(int key) const;
	void ShowFill() const;
	void ShowContents() const;
	bool TableFull() const;
	bool TableEmpty() const;

private:
	int NewSlot(T key, int& tries);
	int FindClosestPrime(int size);
	
	int * table;
	int tableSize;
};



//=============================================================================
//Class:    HashTable
//Function: AssignmentOperator
//=============================================================================
template <class T>
HashTable<T>& HashTable<T>::operator =(const HashTable<T>& rhs){
	delete [] table;
	table = 0;
	tableSize = rhs.tableSize;
	
	
	if(tableSize > 0){
		table = new int [tableSize];
		
		for(int i = 0; i < tableSize; i++)
			table[i] = rhs.table[i];
	}
	return *this;

}

//=============================================================================
//Class:    HashTable
//Function: CopyConstructor
//=============================================================================
template <class T>
HashTable<T>::HashTable(const HashTable<T>& n){
	tableSize = n.tableSize;
	table = 0;
	
	if(tableSize > 0){
		table = new int[tableSize];
		for(int i = 0; i < tableSize; i++)
			table[i] = n.table[i];
	}


}


//=============================================================================
//Class:    HashTable
//Function: Insert
//=============================================================================
template <class T>
int HashTable<T>::Insert(T key){
    int newSlot;
	if(tableSize < 1 || !table) return 0;
	
	int tries = 1;
	
	if(TableFull()){
		cout<<"table is full";
		return 0;
	}
	newSlot = NewSlot(key, tries);
    if(newSlot >= 0)
	   table[newSlot] = key;
    else 
        tries = 0;
	return tries;
}


//=============================================================================
//Class:    HashTable
//Function: Remove
//=============================================================================
template <class T>
int HashTable<T>::Remove(T key){
	if(tableSize < 1 || !table) return 0;
	
	int start =	 key%tableSize;
	int slot = start;
	int tries = 1;
	
	while(table[slot] != key && table[slot] != 0){
		if(tries > tableSize) return 0;
		slot++;
		tries++;
	}
		
	if(table[slot] != key) return 0;
		
	table[slot] = 0;
	
	return tries;
}

//=============================================================================
//Class:    HashTable
//Function: ClearTable
//=============================================================================
template <class T>
void  HashTable<T>::ClearTable(){
	if(tableSize < 1 || !table) return;
	for(int i=0;i<tableSize;i++){
		table[i]=0;
	}
}

//=============================================================================
//Class:    HashTable
//Function: NewSlot
//=============================================================================
template <class T>
int  HashTable<T>::NewSlot(T key, int& tries){
	int start =	 key%tableSize; //makeKey is function that needs to be specialized
	int slot = start;	  

	while(table[slot] != 0){
		if(table[slot] == key){
			cout<<"Duplicates are not allowed";
			return -1;
		}
		slot++;        //start linear probing for slot if it has been threw table more than 3 times
		tries++;
	}

	return slot;
}


//=============================================================================
//Class:    HashTable
//Function: TableFull
//=============================================================================
template <class T>
bool HashTable<T>::TableFull()const{
	if(tableSize < 1 || !table) return true;
	for(int i = 0; i < tableSize; i++){
		if(table[i] == 0)
			return false;
	}
	return true;
}


//=============================================================================
//Class:    HashTable
//Function: ShowContents
//=============================================================================
template <class T>
void HashTable<T>::ShowContents() const{
	if(tableSize < 1 || !table) return;
	
	cout<<"\n\n|Location\tData\t|\n";
	for(int i=0; i < tableSize; i++){
		if(table[i] != 0){
			cout<<"|-----------------------|\n";
			cout<<"|"<<i<<"\t\t"<<table[i]<<"\t|\n";
		}
	}
}


//=============================================================================
//Class:    HashTable
//Function: ShowFill
//=============================================================================
template <class T>
void HashTable<T>::ShowFill() const{
	
	if(tableSize < 1 || !table) return;
	cout<<"\n\n";
	for(int i = 0; i < tableSize; i++){
		cout<<"|--------|\n";
		if(table[i]== 0)
			cout<<"|"<<i<<"\t |\n";
		else
			cout<<"|"<<i<<"\tx|\n";
	}
	cout<<"|--------|\n";
}


//=============================================================================
//Class:    HashTable
//Function: Search
//=============================================================================
template <class T>
int HashTable<T>::Search(int key) const{
	int slot = key % tableSize;
	int tries = 1; //Returns 1 if key is in hash slot
	
	while (table[slot] != 0){
		if (table[slot] == key)
			return tries;
		slot++; //Linear Probing
		tries++;
	}
	
	tries = 0; //If key not found
	return tries;
}


//=============================================================================
//Class:    HashTable
//Function: Constructor (Default)
//=============================================================================
template <class T>
HashTable<T>::HashTable():table(0),tableSize(0){}


//=============================================================================
//Class:    HashTable
//Function: Constructor (Size)
//=============================================================================
template <class T>
HashTable<T>::HashTable(int size){
	
	size = size * 2 + 1;  			//will always be odd
	if(size > MAXTABLESIZE)
		size = MAXTABLESIZE;
	else if (size < 0){
		table = 0;
		size = 0;
		return;
	} 
	size = FindClosestPrime(size);
	

	
	table = new int[size];
	tableSize = size;
	
	for(int l = 0; l< size; l++)  
		table[l] = 0;


	cout<<"table created of size "<<size;
}


//=============================================================================
//Class:    HashTable
//Function: FindClosestPrime
//=============================================================================
template <class T>
int HashTable<T>::FindClosestPrime(int size){
	if(size > MAXTABLESIZE)
		return 0;
		
	int* arr = new int[NUMOFPRIMES];
	
	ifstream myfile;
	myfile.open("first10000prime.txt");
	
	for(int i = 0; i < NUMOFPRIMES ; i++){
		myfile >> arr[i];
	}
	
	int j = 0;
	int begin = 0;
	int end = NUMOFPRIMES-1;
	int jold = -1;
	
	while(jold != j && arr[j] != size){
		if(arr[j] > size)
			end = j-1;
		else
			begin = j+1;
		jold = j;
		j =(begin + end)/2;
	}
	
	int temp = arr[j];
	delete []arr;
	return temp;
}


//=============================================================================
//Class:    HashTable
//Function: Destructor
//=============================================================================
template <class T>
HashTable<T>::~HashTable(){
	delete []table;
}

#endif //HASHTABLE_H
