#pragma once
#include <iostream>
#include <vector>
#include "Piece.h"

class Board
{
public:
	/// <summary> </summary>
	/// <param name="playingAsWhite"> - set this to true if playing from white's perspective </param>
	/// <returns> </returns>
	Board(bool playingAsWhite);

	friend std::ostream& operator<<(std::ostream& os, const Board& b);

	Piece* pieceAt(int i, int j) const;

public:
	bool whiteSide;
	std::vector<std::vector<Piece*>> board;
};

Piece* Board::pieceAt(int i, int j) const
{
	return board[i][j];
}

Board::Board(bool playingAsWhite) : whiteSide(playingAsWhite)
{
	// initialize the board with nullptrs
	for (std::vector<Piece*> row : board)
	{
		for (Piece* p : row)
		{
			p = nullptr;
		}
	}

	board[0][0] = new Rook(!playingAsWhite);
	board[0][1] = new Knight(!playingAsWhite);
	board[0][2] = new Bishop(!playingAsWhite);
	board[0][5] = new Bishop(!playingAsWhite);
	board[0][6] = new Knight(!playingAsWhite);
	board[0][7] = new Rook(!playingAsWhite);

	board[0][3 + (1 && !playingAsWhite)] = new King(!playingAsWhite);
	board[0][4 - (1 && !playingAsWhite)] = new Queen(!playingAsWhite);

	// opposing player pawns
	for (int i = 0; i < 8; i++)
	{
		board[1][i] = new Pawn(!playingAsWhite);
	}

	// player pawns
	for (int i = 0; i < 8; i++)
	{
		board[6][i] = new Pawn(playingAsWhite);
	}

	board[7][0] = new Rook(playingAsWhite);
	board[7][1] = new Knight(playingAsWhite);
	board[7][2] = new Bishop(playingAsWhite);
	board[7][5] = new Bishop(playingAsWhite);
	board[7][6] = new Knight(playingAsWhite);
	board[7][7] = new Rook(playingAsWhite);

	board[7][4 - (1 && playingAsWhite)] = new King(playingAsWhite);
	board[7][3 + (1 && playingAsWhite)] = new Queen(playingAsWhite);
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
	os << "  +---+---+---+---+---+---+---+---+\n";

	for (int i = 0; i < 8; i++)
	{
		os << (b.whiteSide ? (8 - i) : (i + 1)) << " ";
		for (int j = 0; j < 8; j++)
		{
			os << "| " << b.printPiece(i, j) << " ";
		}
		os << "|\n";
		os << "  +---+---+---+---+---+---+---+---+\n";
	}
	os << "    A   B   C   D   E   F   G   H\n";

	return os;
}