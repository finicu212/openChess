#pragma once
#include <string>

class Piece
{
public:
	char virtual getArt()
	{
		return art;
	}

	Piece(char a) : art(a) {};

private:
	char art;
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