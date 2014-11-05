#include <iostream>
#include "hashtable.h"
using namespace std;

int main(){
	HashTable<int> l(4);
	l.ShowFill();
	l.ShowContents();

  return 0;
}
