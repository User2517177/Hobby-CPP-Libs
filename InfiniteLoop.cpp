#include <iostream>
using namespace std;

int main() {
	unsigned long long index = 0;
	while (true) {
		index = index+rand();
		cout << index << endl;
	}
}