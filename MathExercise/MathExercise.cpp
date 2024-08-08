#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
	srand(time(0));
	short Eqn1 = rand();
	short Eqn2 = rand();

	int ans = Eqn1 + Eqn2;
	int UserAns;
	cout << Eqn1 << "+" << Eqn2 << "\n";
	cout << "Input Ans: ";
	cin >> UserAns;
	if (UserAns == ans) {
		cout << "Your ans is " << UserAns << ". Ans is indeed " << ans;
	}
	else {
		cout << "Your ans is " << UserAns << ". Ans is " << ans;
	}
}