#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
	int count = 0;
	int index = 0;
	if (argc > 1) {
		int count = stoi(argv[1]);
	} else {
		cout << "Enter count number: ";
		cin >> count;
	}
		
	do {
		index = index + 1;
		cout << index << endl;
	} while (index < count);
	cout << endl;
	return 0;
}