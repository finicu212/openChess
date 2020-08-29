#pragma once
#include <string>

struct Pos2D
{
	uint8_t x, y;
};

class Piece
{
public:
	char getArt()
	{
		return art;
	}

	void setPos(Pos2D p)
	{
		pos = p;
	}

	Piece(char a) : art(a) {};

private:
	char art;
	Pos2D pos;
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