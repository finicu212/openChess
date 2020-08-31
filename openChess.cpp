#include <iostream>
#include "Board.h"

bool g_playingAsWhite;

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
    g_playingAsWhite = col[0] == 'w' ? true : false;
    Board b;

    std::cout << b << '\n';

    Move firstMove = Move::getMove("e2", "e4");
    if (g_playingAsWhite)
        firstMove = firstMove.invert();

    b.movePiece(firstMove);

    std::cout << b << '\n';
}
