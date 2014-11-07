#include <iostream>
#include "hashtable.h"
using namespace std;

void PrintMenu();

int main(){
	
	int tableSize;
	cout << "Enter Table Size \n>> ";
	cin >> tableSize;
	
	HashTable testHT(tableSize);
	HashTable testAssign;
	int data;
	int tries;

	PrintMenu();
	cout << "-->";
	char choice;
	cin >> choice;
	
	while (choice != 'q' && choice != 'Q'){
		if (choice == '!'){
			HashTable testCopy(testHT);
			cout << "Result:" << "Print New Copy" << endl;
			testCopy.ShowContents();
			testCopy.Insert(-10000);
			cout << "Result: " << "Print Modified Copy" << endl;
			testCopy.ShowContents();
			cout << "Result: " << "Print Original Test List" << endl;
			testHT.ShowContents();
			cout << endl;
		}
		else{
			switch (choice){
				case 'h':
				case 'H': PrintMenu(); 
					break;
				case '+':
					cin >> data;
					tries = testHT.Insert(data);
					if(tries>0)
						cout << "\nInserted " << data << ", " << tries << " tries\n";
					break;
				case '-':
					cin >> data;
					testHT.Remove(data);
					break;
				case 'c':
				case 'C':
					testHT.ClearTable();
					break;
				case 'e':
				case 'E':
					if (testHT.TableEmpty())
						cout << "Result:" << "Table is Empty" << endl;
					else
						cout << "Result:" << "Table is Not Empty" << endl;
					break;
				case 'f':
				case 'F':
					if (testHT.TableFull())
						cout << "Result:" << "Table is Full" << endl;
					else
						cout << "Result:" << "Table is Not Full" << endl;
					break;
				case '#':
					testAssign = testHT;
					testAssign.Insert(-100000);
					cout << "Modify New Table" << endl;
					testAssign.ShowContents();
					cout << "Old Table should not be affected" << endl;
					testHT.ShowContents();
					testAssign.~HashTable();
					cout << "Destroy New Table" << endl;
					cout << "Old Table should not be affected" << endl;
					testHT.ShowContents();
					break;
				case '?':
					cin >> data;
					if (testHT.Search(data) != 0) //TODO: Add number of slots hit to find target
						cout << "Result: " << data << "\tfound" << endl;
					else
						cout << "Result: " << data << "\tnot found" << endl;
					break;
				case 'p':
				case 'P':
					cout << "Print location values and data";
					testHT.ShowContents();
					break;
				case 'z':
				case 'Z':
					testHT.ShowFill();
					break;
				default:
					cout << "Invalid Choice, Please try again" << endl;
			}
		}
		testHT.ShowContents();
		cout << endl;
		cout << "-->";
		cin >> choice;
	}
	
  return 0;
}

void PrintMenu(){
	cout << endl << endl;
	cout << "         -Command Line Options-" << endl;
	cout << "+=====+=====================================+\n";
	cout << "| CMD |  Description                        |\n";
	cout << "+=====+=====================================+\n";
	cout << "| H   | Help: Show Command Line Options     |\n";
	cout << "| +x  | Insert x                            |\n";
	cout << "| -x  | Remove x                            |\n";
	cout << "| C   | Clear the table                     |\n";
	cout << "| E   | Check if table is empty             |\n";
	cout << "| F   | Check if table is full              |\n";
	cout << "| !   | Test copy constructor               |\n";
	cout << "| #   | Test assignment operator            |\n";
	cout << "| ?x  | Search table for x                  |\n";
	cout << "| P   | Print the location values and data  |\n";
	cout << "| Z   | Print a picture of the table        |\n";
	cout << "| Q   | Quit the test program               |\n";
	cout << "+=====+=====================================+";
	cout << endl << endl << endl;
}
