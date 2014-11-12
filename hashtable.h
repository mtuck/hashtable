//=============================================================================
//CS355 Assignment #2
//by Victor Rogers, Martin Tuck, Tyler Yasaka
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

class HashTable;


//=============================================================================
//Class: HashTable
//Author: Rogers,Tuck,Yasaka
//=============================================================================
class HashTable{
public:
	HashTable();
	HashTable(int size);
	HashTable(const HashTable& n);
	HashTable& operator =(const HashTable& rhs);
	~HashTable();
	
	int Insert(int key);
	int Remove(int key);
	void ClearTable();
	
	int Search(int key) const;
	void ShowFill() const;
	void ShowContents() const;
	bool TableFull() const;
	bool TableEmpty() const;

private:
	int NewSlot(int key, int& tries);
	int FindClosestPrime(int size);
	
	int * table;
	int tableSize;
};



//=============================================================================
//Class:    HashTable
//Function: AssignmentOperator
//Author: Rogers,Tuck,Yasaka
//=============================================================================
HashTable& HashTable::operator =(const HashTable& rhs){
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
//Author: Rogers,Tuck,Yasaka
//=============================================================================
HashTable::HashTable(const HashTable& n){
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
//Author: Rogers,Tuck,Yasaka
//=============================================================================
int HashTable::Insert(int key){
    int result = 0;
    int newSlot;
	if(tableSize > 0 && table){
	
	   if(TableFull()){
	       cout<<"Table is full\t";
	   }
	   else{
	       int tries = 1;
           newSlot = NewSlot(key, tries);
           if(newSlot >= 0){
	           table[newSlot] = key;
               result = tries;
           }
           else
           	cout<<"Item could not be added\n";
        }
    }

    return result;
}


//=============================================================================
//Class:    HashTable
//Function: Remove
//Precondition: Key is value of item to be removed.
//Postcondition: Item will be removed if in table.
//Author: Rogers,Tuck,Yasaka
//=============================================================================
int HashTable::Remove(int key){
	int result = 0;

	int slot = key % tableSize;
	int tries = 1; //Returns 1 if key is in hash slot
	
	while (table[slot] != 0 && result == 0 && tries <= tableSize){
		if (table[slot] == key){
			table[slot] = -1;
			result = ++tries;
			break;
		}
		slot = (slot+1) % tableSize; //Linear Probing
		tries++;
	}
	

	
	return result;
}

//=============================================================================
//Class:    HashTable
//Function: ClearTable
//Precondition: N/A
//Postcondition: Table will be empty.
//Author: Rogers,Tuck,Yasaka
//=============================================================================
void  HashTable::ClearTable(){
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
//Author: Rogers,Tuck,Yasaka
//=============================================================================
int  HashTable::NewSlot(int key, int& tries){
    int result = -1;

	int slot = key%tableSize;

	while(table[slot] != 0 && table[slot] != -1 && table[slot] !=key && tries <= tableSize){
		slot = (slot+1) % tableSize;
		tries++;
	}
	if(table[slot] == key)
		cout<<"Duplicates are not allowed";
    else if(table[slot]==0 || table[slot] == -1)
        result = slot;

	return result;
}


//=============================================================================
//Class:    HashTable
//Function: TableFull
//Precondition: N/A
//Postcondition: Returns true if table is full.
//Author: Rogers,Tuck,Yasaka
//=============================================================================
bool HashTable::TableFull()const{
    bool result = true;
	if(tableSize > 0 && table){
        int slot = 0;
        while(slot < tableSize && result){
            if(table[slot] == 0 || table[slot] == -1)
                result = false;
            slot++;
        }
    }
	return result;
}


//=============================================================================
//Class:    HashTable
//Function: TableEmpty
//Precondition: N/A
//Postcondition: Returns true if table is empty.
//Author: Rogers,Tuck,Yasaka
//=============================================================================
bool HashTable::TableEmpty()const{
    bool result = true;
	if(tableSize > 0 && table){
        int slot = 0;
        while(slot < tableSize && result){
            if(table[slot] > 0)
                result = false;
            slot++;
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
//Author: Rogers,Tuck,Yasaka
//=============================================================================
void HashTable::ShowContents() const{
	if(tableSize > 0 && table){
	
	   cout<<"\n\n|Location\tData\t|\n";
	   for(int i=0; i < tableSize; i++){
		  if(table[i] > 0){
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
//Author: Rogers,Tuck,Yasaka
//=============================================================================
void HashTable::ShowFill() const{
	
	if(tableSize > 0 && table){
	   cout<<"\n\n";
	   for(int i = 0; i < tableSize; i++){
		  cout<<"|--------|\n";
		  if(table[i] <= 0)
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
//Author: Rogers,Tuck,Yasaka
//=============================================================================
int HashTable::Search(int key) const{
    int result = 0;

	int slot = key % tableSize;
	int tries = 1; //Returns 1 if key is in hash slot
	
	while (table[slot] != 0 && result == 0 && tries <= tableSize){
		if (table[slot] == key)
			result = tries;
		slot = (slot+1) % tableSize; //Linear Probing
		tries++;
	}
	
	return result;
}


//=============================================================================
//Class:    HashTable
//Function: Constructor (Default)
//Author: Rogers,Tuck,Yasaka
//=============================================================================
HashTable::HashTable():table(0),tableSize(0){}


//=============================================================================
//Class:    HashTable
//Function: Constructor (Size)
//Author: Rogers,Tuck,Yasaka
//=============================================================================
HashTable::HashTable(int size){

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
//Author: Rogers,Tuck,Yasaka
//=============================================================================
int HashTable::FindClosestPrime(int size){
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
//Author: Rogers,Tuck,Yasaka
//=============================================================================
HashTable::~HashTable(){
	delete []table;
	table = 0;
}

#endif //HASHTABLE_H
