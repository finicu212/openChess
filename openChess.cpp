#include <iostream>
#include "Board.h"

int main()
{
    Board b(true);
    Piece* p = new Pawn(true);

    std::cout << b;
}
