#include <iostream>
#include "Board.h"

Board g_board;

int main()
{
    std::string col;
    std::cout << "Pick your color (w / b): ";
    std::cin >> col;
    g_board.setPlayingAsWhite(col[0] == 'w');

    uint8_t gameStatus;
    while ((gameStatus = g_board.gameOver()) == 0)
    {
        std::cout << g_board << '\n';

        Move move;
        do
        {
            std::string plyMoveSrc, plyMoveDest;
            std::cout << (g_board.whitesTurn() ? "white's" : "black's") << " move (src dest):";
            std::cin >> plyMoveSrc >> plyMoveDest;

            move = Move::getMove(plyMoveSrc, plyMoveDest);
            if (Move::outOfBounds(move))
            {
                move.setIntention(255);
            }
            else
            {
                move.setIntention(g_board.findIntention(move));
            }

        } while (!g_board.isValidMove(move));

        g_board.movePiece(move);
    }

    switch (gameStatus)
    {
    case 1:
        std::cout << "Checkmate! " << (!g_board.whitesTurn() ? "white" : "black") << " won!\n";
        break;
    case 2:
        std::cout << "Stalemate! No moves left for " << (g_board.whitesTurn() ? "white" : "black") << '\n';
        break;
    case 3:
        std::cout << "Stalemate due to lack of material\n";
        break;
    default:
        std::cout << "Game ended because of unknown cause\n";
        break;
    }

    std::cout << g_board;
}
