#include <iostream>
using namespace std;

int main()
{
	short HotTemp;
	short ColdTemp;
	short RoomTemp;
	
	cout << "Input hot side of temperature: ";
	cin >> HotTemp;
	cout << "Input cold side of temperature: ";
	cin >> ColdTemp;
	cout << "Input room temperature: ";
	cin >> RoomTemp;
	cout << "Now calculating equibrilium" << endl;
	do {
		HotTemp = HotTemp - 1;
		ColdTemp = ColdTemp + 1;
		if (HotTemp <= RoomTemp) {
			cout << "Hot temp reached room temp. Cold temp when hot temp is room temp: " << ColdTemp;
			return ColdTemp;
		}
		else if (HotTemp == ColdTemp) {
			cout << "Equilibrium reached before room temp. Equilibrium temp is " << HotTemp;
			return HotTemp;
		}
	} while(true);
}