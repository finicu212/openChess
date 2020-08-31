#include <iostream>
#include "Board.h"

bool g_playingAsWhite;
Board g_board;

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

    bool whitesTurn = true;
    while (!gameOver(g_board))
    {
        std::cout << g_board << '\n';

        std::string plyMoveSrc, plyMoveDest;
        std::cout << "Enter move (src_square dest_square):";
        std::cin >> plyMoveSrc >> plyMoveDest;

        Move move = Move::getMove(plyMoveSrc, plyMoveDest);
        if (whitesTurn)
        {
            move = move.invert();
        }

        g_board.movePiece(move);
    }


    std::cout << g_board << '\n';
}
