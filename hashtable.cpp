const int NUMOFPRIMES = 10000;  
const int MAXTABLESIZE = 104729;   //max number of key the constructor will take is MAXTABLESIZE/2

int findClosestPrime(int size);
#include "hashtable.h"
#include <iostream>
#include<fstream>

using namespace std;

template <class T>
HashTable<T>::HashTable(){}


template <class T>
HashTable<T>::HashTable(int size){
	size = size * 2 + 1;  //will always be odd
	size = findClosestPrime(size);
	
	table = new int[size];
	cout<<"table created of size "<<size;
}


int findClosestPrime(int size){
	if(size > MAXTABLESIZE)
		return 0;
		
	int* arr = new int[NUMOFPRIMES];

	int line;
	
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
	
	return arr[j];

}


template <class T>
HashTable<T>::~HashTable(){
	delete table;
}
