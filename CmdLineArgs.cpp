#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    int index = 0;
    cout << "Arg count: " << argc << endl;
    do {
        index = index + 1;
        if (index < argc) {
            cout << "Text of arg" << index << ": " << argv[index] << endl;
        }
    } while (index < argc);
    return 0;
}