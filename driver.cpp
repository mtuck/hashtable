#include <iostream>
#include "hashtable.h"
using namespace std;

int main(){
	HashTable<int> l(4);
	cout<<endl<<l.Insert(1)<<endl;
	l.Insert(2);
	l.Insert(999);
	l.Insert(1000);
	l.Insert(2001);
	l.Insert(2005);
	cout<<l.Insert(2009)<<endl;
	l.Insert(300010);
	l.ShowFill();
	l.ShowContents();

  return 0;
}
