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

	bool shaded(int i, int j) const
	{
		return board[i][j].isShaded();
	}

public:
	Square board[8][8];
};


Board::Board(bool playingAsWhite)
{
	// opposing player major pieces TODO
	bool shadeSquare = false;
	for (int i = 0; i < 8; i++)
	{
		board[0][i] = Square(shadeSquare);
		shadeSquare = !shadeSquare;
	}

	// opposing player pawns
	shadeSquare = !shadeSquare;
	for (int i = 0; i < 8; i++)
	{
		board[1][i] = Square(shadeSquare, new Pawn());
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
		board[6][i] = Square(shadeSquare, new Pawn());
		shadeSquare = !shadeSquare;
	}

	// player major pieces TODO
	shadeSquare = !shadeSquare;
	for (int i = 0; i < 8; i++)
	{
		board[7][i] = Square(shadeSquare);
		shadeSquare = !shadeSquare;
	}
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
	for (int i = 0; i < 8; i++)
	{
		os << i << " ";
		for (int j = 0; j < 8; j++)
		{
			os << "| ";

			if (b.shaded(i, j))
				os << ".";
			else
				os << " ";

			os << " ";
		}
		os << "|\n";
	}

	return os;
}