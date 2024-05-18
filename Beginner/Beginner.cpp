#include <iostream>
using namespace std;

int main() {
	int X = 0;
	int Y = 0;
	cout << "Enter value for X: ";
	cin >> X;
	cout << "Enter value for Y: ";
	cin >> Y;
	int out = X + Y;
	cout << "Out is: " << out << endl;
	cout << "Errorlevel depends on math" << endl;
	system("pause > nul");
	system("%comspec%");
	return out;
}