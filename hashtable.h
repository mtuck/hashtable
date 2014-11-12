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
//Struct: Slot
//Author: Rogers,Tuck,Yasaka
//=============================================================================
struct slot{
	int value;
	//Tells whether or not this is an available slot for insertion
	//Will become true when a value is inserted
	bool filled;
	//Tells whether or not this is a valid slot for search and removal
	//Will become false when a value is removed
	bool active;
	slot():value(0),filled(false),active(true){};
};


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
	int FindClosestPrime(int size) const;
	int Absolute(int number) const;
	void Rehash();
	
	slot * table;
	int tableSize;
	int originalSize;	//Allows table to be fully reset
	int slotsTaken;
};


//=============================================================================
//Class:    HashTable
//Function: AssignmentOperator
//Author: Rogers,Tuck,Yasaka
//=============================================================================
HashTable& HashTable::operator =(const HashTable& rhs){
	delete [] table;
	table = 0;
	originalSize = tableSize = rhs.tableSize;
	slotsTaken = rhs.slotsTaken;
	
	if(tableSize > 0){
		table = new slot [tableSize];
		for(int i = 0; i < tableSize; i++) {
			table[i].value = rhs.table[i].value;
			table[i].filled = rhs.table[i].filled;
			table[i].active = rhs.table[i].active;
		}
	}
	
	return *this;
}

//=============================================================================
//Class:    HashTable
//Function: CopyConstructor
//Author: Rogers,Tuck,Yasaka
//=============================================================================
HashTable::HashTable(const HashTable& n){
	originalSize = tableSize = n.tableSize;
	slotsTaken = n.slotsTaken;
	table = 0;
	
	if(tableSize > 0){
		table = new slot[tableSize];
		for(int i = 0; i < tableSize; i++) {
			table[i].value = n.table[i].value;
			table[i].filled = n.table[i].filled;
			table[i].active = n.table[i].active;
		}
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
	       cout<<"table is full";
	   }
	   else{
	       int tries = 1;
           newSlot = NewSlot(key, tries);
           if(newSlot >= 0){
	           table[newSlot].value = key;
	           table[newSlot].filled = true;
	           table[newSlot].active = true;
               result = tries;
               //Keep track of taken slots
               slotsTaken++;
               //If number of taken slots > half table size, rehash the table
               if(slotsTaken > (tableSize/2))
			       Rehash();
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
//Author: Rogers,Tuck,Yasaka
//=============================================================================
int HashTable::Remove(int key){
    int result = 0;

	if(tableSize > 0 && table){
	
	   int current_slot = Absolute(key%tableSize);
       int tries = 1;
	
		//Falls out of loop if the remove is performed, if an unfilled slot is encountered, or the whole table has been searched
	    while(result==0 && table[current_slot].filled && tries<=tableSize){
			//If slot holds value and is an active slot
			if(table[current_slot].value == key && table[current_slot].active){
				table[current_slot].active = false;
				result = tries;
			}
		    current_slot = (current_slot+1) % tableSize; //loops back to beginning of table when the end is reached
		    tries++;
	    }
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
	   delete []table;
	   tableSize = originalSize;
	   table = new slot [tableSize];
	   slotsTaken = 0;
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
    bool duplicate = false;

	int current_slot;
	
	current_slot = Absolute(key%tableSize);

	//Loop terminates if empty slot is found, an inactive slot is found, if all slots have been checked,
	//or if an unfilled active slot holds the same value as key
	while(table[current_slot].filled && table[current_slot].active && tries <= tableSize && !duplicate){
		//if slot holds the same value, it is a duplicate
		if(table[current_slot].value == key) {
			cout << "Duplicates are not allowed";
			duplicate = true;
		}
		current_slot = (current_slot+1) % tableSize;
		tries++;
	}
    //If slot is unfilled or inactive, and if a duplicate wasn't found, return the slot.
    if( (!table[current_slot].filled || !table[current_slot].active) && !duplicate)
        result = current_slot;

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
    bool full = true;
	if(tableSize > 0 && table){
        int current_slot = 0;
        while(current_slot < tableSize && full){
			full = (table[current_slot].filled && table[current_slot].active);
            current_slot++;
        }
    }
	return full;
}


//=============================================================================
//Class:    HashTable
//Function: TableEmpty
//Precondition: N/A
//Postcondition: Returns true if table is empty.
//Author: Rogers,Tuck,Yasaka
//=============================================================================
bool HashTable::TableEmpty()const{
    bool empty = true;
	if(tableSize > 0 && table){
        int current_slot = 0;
        while(current_slot < tableSize && empty){
			empty = (!table[current_slot].filled || !table[current_slot].active);
            current_slot++;
        }
    }
	return empty;
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
		  if(table[i].filled && table[i].active){
		  	 cout<<"|-----------------------|\n";
			 cout<<"|"<<i<<"\t\t"<<table[i].value<<"\t|\n";
		  }
	   }
    }
}


//=============================================================================
//Class:    HashTable
//Function: ShowFill
//Precondition: N/A
//Postcondition: Show which records are filled and which are empty.
//This of course does not mean that the slot is active - only that it is
//unavailable for insertion.
//Author: Rogers,Tuck,Yasaka
//=============================================================================
void HashTable::ShowFill() const{
	
	if(tableSize > 0 && table){
	   cout<<"\n\n";
	   for(int i = 0; i < tableSize; i++){
		  cout<<"|--------|\n";
		  if(table[i].filled && table[i].active)
			 cout<<"|"<<i<<"\tx|\n";
		  else
			 cout<<"|"<<i<<"\t |\n";
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

	int current_slot = Absolute(key % tableSize);
	int tries = 1; //Returns 1 if key is in hash slot
	//Breaks out of loop if unfilled slot is encountered, if a match is found,
	//or if the entire table has been searched
	while (table[current_slot].filled && result == 0 && tries <= tableSize){
		//If value matches and slot is active
		if (table[current_slot].value == key && table[current_slot].active)
			result = tries;
		current_slot = (current_slot+1) % tableSize; //Linear Probing
		tries++;
	}
	
	return result;
}


//=============================================================================
//Class:    HashTable
//Function: Constructor (Default)
//Author: Rogers,Tuck,Yasaka
//=============================================================================
HashTable::HashTable():table(0),tableSize(0),originalSize(0),slotsTaken(0){}


//=============================================================================
//Class:    HashTable
//Function: Constructor (Size)
//Author: Rogers,Tuck,Yasaka
//=============================================================================
HashTable::HashTable(int size){

	slotsTaken = 0;

	if (size < 0){
		table = 0;
		size = 0;
	}
	
    else {

	   size = size * 2 + 1;  			//will always be odd
	   if(size > MAXTABLESIZE)
		  size = MAXTABLESIZE;
	   size = FindClosestPrime(size);
	
	   table = new slot[size];
	   tableSize = size;
	
	   //for(int l = 0; l< size; l++)  
		  //table[l].value = 0;
		  //Don't need this because struct initializes values automatically

    }
    
    originalSize = tableSize;

	cout<<"table created of size "<<size;
}

//=============================================================================
//Class:    HashTable
//Function: Rehash
//Author: Rogers,Tuck,Yasaka
//Description: When table gets too full, creates a new table twice as big
//and rehashes all values to the new table.
//=============================================================================
void HashTable::Rehash(){
	int newsize = tableSize * 2 + 1;  			//will always be odd
	int current_slot;
	int key;
	if(newsize > MAXTABLESIZE)
		newsize = MAXTABLESIZE;
	newsize = FindClosestPrime(newsize);
	slot * newtable = new slot[newsize];
	slotsTaken = 0;
	//Iterates through the current table
	for(int i=0;i<tableSize;i++){
		//Checks if the slot has a value to copy
		if(table[i].filled && table[i].active){
			key = table[i].value;
			current_slot = Absolute(key%newsize);
			//Loop terminates once empty slot is found
			while(newtable[current_slot].filled)
				current_slot = (current_slot+1) % newsize;
			newtable[current_slot].value = key;
			newtable[current_slot].filled = true;
			newtable[current_slot].active = true;
			slotsTaken++;
		}
	}
	//Reset old table and assign new table to it
	delete []table;
	table = newtable;
	tableSize = newsize;
	cout << "The table has been rehashed." << endl;
}


//=============================================================================
//Class:    HashTable
//Function: Absolute
//Author: Rogers,Tuck,Yasaka
//Descripion: Returns absolute value of input
//=============================================================================
int HashTable::Absolute(int number)const{
	if(number >= 0)
		return number;
	else
		return -1 * number;
}



//=============================================================================
//Class:    HashTable
//Function: FindClosestPrime
//Author: Rogers,Tuck,Yasaka
//=============================================================================
int HashTable::FindClosestPrime(int size)const{
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
