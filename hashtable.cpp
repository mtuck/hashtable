const int NUMOFPRIMES = 10000;  
const int MAXTABLESIZE = 104729;   //max number of key the constructor will take is MAXTABLESIZE/2

int findClosestPrime(int size);
#include "hashtable.h"
#include <iostream>
#include<fstream>
#include <new>

using namespace std;

template <class T>
HashTable<T>::HashTable(){}





template <class T>
HashTable<T>::HashTable(int size){
	size = size * 2 + 1;  //will always be odd
	size = findClosestPrime(size);
	
    table = new (nothrow) int[size];
    tableSize = size;
	cout<<"table created of size "<<size;
}


template <class T>
void HashTable<T>::showFill(){
    for(int i = 0; i < 5; i++){
        cout<<"|---------------------|";
        if(table[i] == 0)
            cout<<"|"<<i<<"\t\t\t|";
        else
            cout<<"|"<<i<<"\tX\t|";
    }
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
	
	int j;
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

    myfile.close();
	int temp = arr[j];
    delete []arr;
	return temp;

}


template <class T>
HashTable<T>::~HashTable(){
	delete []table;
}
