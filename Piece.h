#pragma once
#include <string>

class Piece
{
public:
	char getArt()
	{
		return art;
	}

	void setPos(uint8_t i, uint8_t j)
	{
		row = i;
		col = j;
	}

	Piece(char a) : art(a) {};

private:
	char art;
	uint8_t row, col;
};

class Pawn : public Piece
{
public:
	Pawn(bool isWhite) : Piece(isWhite ? 'P' : 'p') {};
};

class Rook : public Piece
{
public:
	Rook(bool isWhite) : Piece(isWhite ? 'R' : 'r') {};
};

class Knight : public Piece
{
public:
	Knight(bool isWhite) : Piece(isWhite ? 'N' : 'n') {};
};

class Bishop : public Piece
{
public:
	Bishop(bool isWhite) : Piece(isWhite ? 'B' : 'b') {};
};

class Queen : public Piece
{
public:
	Queen(bool isWhite) : Piece(isWhite ? 'Q' : 'q') {};
};

class King : public Piece
{
public:
	King(bool isWhite) : Piece(isWhite ? 'K' : 'k') {};
};