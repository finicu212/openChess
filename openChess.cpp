#include <iostream>
#include "Board.h"

/// <summary> </summary>
/// <param name="b"> - the chess board object </param>
/// <returns> why the game ended. 1 = checkmate, 2 = no moves left, 3 = not enough material, TODO add more</returns>
int gameOver(const Board& b)
{

    return 0;
}

bool move(Square& o, Square& d)
{
    d.setPiece(o.getPiece());
    o.setPiece(nullptr);
    return true;
}

int main()
{
    char col;
    std::cout << "Pick your color (w / b): ";
    std::cin >> col;

    Board b(col == 'w' ? true : false);

    while (!gameOver(b))
    {
        std::cout << b << "\nEnter your move:";

        std::string move;
        std::cin >> move;
    }
    
}
