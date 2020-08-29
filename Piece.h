#pragma once
#include <string>
#include "Move.h"

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

	virtual bool isValidMove(const Move& move) = 0;

	Piece(char a) : art(a) {};

private:
	char art;
	Pos2D pos;
};

class Pawn : public Piece
{
public:
	Pawn(bool isWhite) : Piece(isWhite ? 'P' : 'p') {};

	bool isValidMove(const Move& move) override
	{
		return false;
	}
};

class Rook : public Piece
{
public:
	Rook(bool isWhite) : Piece(isWhite ? 'R' : 'r') {};

	bool isValidMove(const Move& move) override
	{
		return false;
	}
};

class Knight : public Piece
{
public:
	Knight(bool isWhite) : Piece(isWhite ? 'N' : 'n') {};

	bool isValidMove(const Move& move) override
	{
		return false;
	}
};

class Bishop : public Piece
{
public:
	Bishop(bool isWhite) : Piece(isWhite ? 'B' : 'b') {};

	bool isValidMove(const Move& move) override
	{
		return false;
	}
};

class Queen : public Piece
{
public:
	Queen(bool isWhite) : Piece(isWhite ? 'Q' : 'q') {};

	bool isValidMove(const Move& move) override
	{
		return false;
	}
};

class King : public Piece
{
public:
	King(bool isWhite) : Piece(isWhite ? 'K' : 'k') {};

	bool isValidMove(const Move& move) override
	{
		return false;
	}
};