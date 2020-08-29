#include <iostream>
#include "Board.h"

/// <summary> </summary>
/// <param name="b"> - the chess board object </param>
/// <returns> why the game ended. 1 = checkmate, 2 = no moves left, 3 = not enough material, TODO add more</returns>
int gameOver(const Board& b)
{

    return 0;
}

int main()
{
    std::string col;
    std::cout << "Pick your color (w / b): ";
    std::cin >> col;
    Board b(col[0] == 'w' ? true : false);

    while (!gameOver(b))
    {
        std::cout << b << "\nEnter your move:";

        std::string move;
        std::cin >> move;
    }
    
}
