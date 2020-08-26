#pragma once
#include "Piece.h"

class Square
{
public:
	Square(bool s, Piece* p)	: shaded(s), pieceHere(p) {};
	Square(bool s)				: shaded(s), pieceHere(nullptr) {};
	Square() {};

	bool isShaded() const
	{
		return shaded;
	}

private:
	bool shaded;
	Piece* pieceHere;
};