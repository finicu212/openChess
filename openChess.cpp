#include <iostream>
#include "Board.h"

int main()
{
    char col;
    std::cout << "Pick your color (w / b): ";
    std::cin >> col;

    Board b(col == 'w' ? true : false);

    std::cout << b;
}
