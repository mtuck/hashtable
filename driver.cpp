#include <iostream>
#include "hashtable.h"
using namespace std;

int main(){
	HashTable<int> l(4);
	cout<<endl<<l.Insert(1)<<endl;
	l.Insert(2);
	l.Insert(999);
	l.Insert(1000);
	cout<<endl<<l.Insert(2001)<<endl;
	l.Insert(2005);
	cout<<endl<<l.Insert(2009)<<endl;
	l.Insert(300010);
	cout<<endl<<l.Remove(0)<<endl;
	cout<<endl<<l.Remove(2001)<<endl;  //2001 takes 2 tries to add and 2 to remove
	l.ShowContents();
	HashTable<int> j;
	j.Remove(2);
	j.ShowContents();
	l.ShowContents();

  return 0;
}
