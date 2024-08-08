#include <iostream>

int main()
{
    unsigned short index = 0;
    do {
        index = index++;
        std::cout << index << "\n";
        if (index == 0) {
            return 0;
        }
    } while (true);
}