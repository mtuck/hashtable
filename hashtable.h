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
//Precondition: Key is value of item to be inserted.
//Postcondition: Item will be inserted if there is at least 1 slot available
//in table.
//=============================================================================
template <class T>
int HashTable<T>::Insert(T key){
    int result = 0;
    int newSlot;
	if(tableSize > 0 && table){
	
	   if(TableFull()){
	       cout<<"table is full";
	   }
	   else{
	       int tries = 1;
           newSlot = NewSlot(key, tries);
           if(newSlot >= 0){
	           table[newSlot] = key;
               result = tries;
           }
        }
    }

    return result;
}


//=============================================================================
//Class:    HashTable
//Function: Remove
//Precondition: Key is value of item to be removed.
//Postcondition: Item will be removed if in table. 
//=============================================================================
template <class T>
int HashTable<T>::Remove(T key){
    int result = 0;

	if(tableSize > 0 && table){
	
	   int slot = key%tableSize;
       int tries = 1;
	
	    while(table[slot] != key && table[slot] != 0 && tries <= tableSize){
		    slot++;
		    tries++;
	    }
		
	    if(table[slot] == key){
    	    table[slot] = 0;
            result = tries;
        }
    }
	
	return result;
}

//=============================================================================
//Class:    HashTable
//Function: ClearTable
//Precondition: N/A
//Postcondition: Table will be empty.
//=============================================================================
template <class T>
void  HashTable<T>::ClearTable(){
	if(tableSize > 0 && table){
	   for(int i=0;i<tableSize;i++)
		  table[i]=0;
    }
}

//=============================================================================
//Class:    HashTable
//Function: NewSlot
//Precondition: Key is item to be inserted by Insert function,
//tries is an integer set to value 1, and table is not full.
//Postcondition: Item will be inserted into table, tries will be set to number
//of attempts made at finding an available slot.
//=============================================================================
template <class T>
int  HashTable<T>::NewSlot(T key, int& tries){
    int result = -1;

	int slot = key%tableSize;

	while(table[slot] != 0 && table[slot]!=key){
		slot++;
		tries++;
	}
	if(table[slot] == key)
		cout<<"Duplicates are not allowed";
    else if(table[slot]==0)
        result = slot;

	return result;
}


//=============================================================================
//Class:    HashTable
//Function: TableFull
//Precondition: N/A
//Postcondition: Returns true if table is full.
//=============================================================================
template <class T>
bool HashTable<T>::TableFull()const{
    bool result = true;
	if(tableSize > 0 && table){
        int slot = 0;
        while(slot < tableSize && result){
            if(table[slot] == 0)
                result = false;
        }
    }
	return result;
}


//=============================================================================
//Class:    HashTable
//Function: ShowContents
//Precondition: N/A
//Postcondition: Shows the data contents of the table, including value and
//location of each record.
//=============================================================================
template <class T>
void HashTable<T>::ShowContents() const{
	if(tableSize > 0 && table){
	
	   cout<<"\n\n|Location\tData\t|\n";
	   for(int i=0; i < tableSize; i++){
		  if(table[i] != 0){
		  	 cout<<"|-----------------------|\n";
			 cout<<"|"<<i<<"\t\t"<<table[i]<<"\t|\n";
		  }
	   }
    }
}


//=============================================================================
//Class:    HashTable
//Function: ShowFill
//Precondition: N/A
//Postcondition: Show which records are filled and which are empty.
//=============================================================================
template <class T>
void HashTable<T>::ShowFill() const{
	
	if(tableSize > 0 && table){
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
}


//=============================================================================
//Class:    HashTable
//Function: Search
//Precondition: N/A
//Postcondition: Return number of tries to find an item in a table, or 0 if
//not found.
//=============================================================================
template <class T>
int HashTable<T>::Search(int key) const{
    int result = 0;

	int slot = key % tableSize;
	int tries = 1; //Returns 1 if key is in hash slot
	
	while (table[slot] != 0 && result == 0 && tries <= tableSize){
		if (table[slot] == key)
			result = tries;
		slot++; //Linear Probing
		tries++;
	}
	
	return result;
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

	if (size < 0){
		table = 0;
		size = 0;
	}
	
    else {

	   size = size * 2 + 1;  			//will always be odd
	   if(size > MAXTABLESIZE)
		  size = MAXTABLESIZE;
	   size = FindClosestPrime(size);
	
	   table = new int[size];
	   tableSize = size;
	
	   for(int l = 0; l< size; l++)  
		  table[l] = 0;

    }

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
