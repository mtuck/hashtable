#ifndef HASHTABLE_H
#define HASHTABLE_H
#include<fstream>

const int NUMOFPRIMES = 10000;  
const int MAXTABLESIZE = 104729;   //max number of key the constructor will take is MAXTABLESIZE/2

int findClosestPrime(int size);

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
	void ShowFill() const;
	void ShowContents() const;
	~HashTable();
private:
	int * table;
	int tableSize;
};



template <class T>
void HashTable<T>::ShowContents() const{
	cout<<"\n\n|Location\tData\t|\n";
	for(int i=0; i < tableSize; i++){
		if(table[i] != 0){
			cout<<"|-----------------------|\n";
			cout<<"|"<<i<<"\t\t"<<table[i]<<"\t|\n";
		
		}
			
	}



}




template <class T>
void HashTable<T>::ShowFill() const{
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

template <class T>
HashTable<T>::HashTable(){}

template <class T>
HashTable<T>::HashTable(int size){
	size = size * 2 + 1;  			//will always be odd
	size = findClosestPrime(size);
	
	table = new int[size];
	tableSize = size;
	
	for(int l = 0; l< size; l++)  
		table[l] = 0;
	table[2]=2000;
	table[1]=99999;

	cout<<"table created of size "<<size;
}






int findClosestPrime(int size){
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


template <class T>
HashTable<T>::~HashTable(){
	delete []table;
}

#endif //HASHTABLE_H
