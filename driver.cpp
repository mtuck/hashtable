#include <iostream>
#include "hashtable.h"
using namespace std;

int main(){
	HashTable<int> l(4);
	l.Insert(1);
	l.Insert(2);
	l.Insert(999);
	l.ShowFill();
	l.ShowContents();

  return 0;
}
