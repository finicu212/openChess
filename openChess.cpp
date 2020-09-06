#include <iostream>
#include "Board.h"

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
    g_board.setPlayingAsWhite(col[0] == 'w');

    while (!gameOver(g_board))
    {
        std::cout << g_board << '\n';

        Move move;
        do
        {
            std::string plyMoveSrc, plyMoveDest;
            std::cout << "Enter valid move for " << (g_board.whitesTurn() ? "white" : "black") << " (src_square dest_square):";
            std::cin >> plyMoveSrc >> plyMoveDest;

            move = Move::getMove(plyMoveSrc, plyMoveDest);
            move.setIntention(g_board.findIntention(move));
        } while (!g_board.isValidMove(move));

        g_board.movePiece(move);
    }

    std::cout << g_board << '\n';
}
