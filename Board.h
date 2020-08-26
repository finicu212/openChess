#pragma once
#include <iostream>
#include "Square.h"


class Board
{
public:
	/// <summary> </summary>
	/// <param name="playingAsWhite"> - set this to true if playing from white's perspective </param>
	/// <returns> </returns>
	Board(bool playingAsWhite);

	friend std::ostream& operator<<(std::ostream& os, const Board& b);

	Square squareAt(int i, int j) const;

public:
	bool whiteSide;
	Square board[8][8];
};

Square Board::squareAt(int i, int j) const
{
	return board[i][j];
}

Board::Board(bool playingAsWhite) : whiteSide(playingAsWhite)
{
	bool shadeSquare = !playingAsWhite;
	board[0][0] = Square(shadeSquare, new Rook(!playingAsWhite));
	board[0][1] = Square(!shadeSquare, new Knight(!playingAsWhite));
	board[0][2] = Square(shadeSquare, new Bishop(!playingAsWhite));
	board[0][5] = Square(!shadeSquare, new Bishop(!playingAsWhite));
	board[0][6] = Square(shadeSquare, new Knight(!playingAsWhite));
	board[0][7] = Square(!shadeSquare, new Rook(!playingAsWhite));

	board[0][3 + (1 && !playingAsWhite)] = Square(!shadeSquare, new King(!playingAsWhite));
	board[0][4 - (1 && !playingAsWhite)] = Square(shadeSquare, new Queen(!playingAsWhite));

	// opposing player pawns
	//shadeSquare = true;
	for (int i = 0; i < 8; i++)
	{
		board[1][i] = Square(shadeSquare, new Pawn(!playingAsWhite));
		shadeSquare = !shadeSquare;
	}

	// empty squares
	shadeSquare = !shadeSquare;
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[i][j] = Square(shadeSquare);
			shadeSquare = !shadeSquare;
		}
		shadeSquare = !shadeSquare;
	}

	// player pawns
	for (int i = 0; i < 8; i++)
	{
		board[6][i] = Square(shadeSquare, new Pawn(playingAsWhite));
		shadeSquare = !shadeSquare;
	}

	board[7][0] = Square(!shadeSquare, new Rook(playingAsWhite));
	board[7][1] = Square(shadeSquare, new Knight(playingAsWhite));
	board[7][2] = Square(!shadeSquare, new Bishop(playingAsWhite));
	board[7][5] = Square(shadeSquare, new Bishop(playingAsWhite));
	board[7][6] = Square(!shadeSquare, new Knight(playingAsWhite));
	board[7][7] = Square(shadeSquare, new Rook(playingAsWhite));

	board[7][4 - (1 && playingAsWhite)] = Square(!shadeSquare, new King(playingAsWhite));
	board[7][3 + (1 && playingAsWhite)] = Square(shadeSquare, new Queen(playingAsWhite));
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
	os << "  +---+---+---+---+---+---+---+---+\n";

	for (int i = 0; i < 8; i++)
	{
		os << (b.whiteSide ? (8 - i) : (i + 1)) << " ";
		for (int j = 0; j < 8; j++)
		{
			os << "| " << b.squareAt(i, j) << " ";
		}
		os << "|\n";
		os << "  +---+---+---+---+---+---+---+---+\n";
	}
	os << "    A   B   C   D   E   F   G   H\n";

	return os;
}