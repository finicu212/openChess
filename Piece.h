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