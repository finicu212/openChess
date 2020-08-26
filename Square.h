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

	Piece* getPiece() const
	{
		return pieceHere;
	}

	void setPiece(Piece* p)
	{
		pieceHere = p;
	}

	friend std::ostream& operator<<(std::ostream& os, const Square& sq)
	{
		Piece* p = sq.getPiece();
		if (p != nullptr)
			os << p->getArt();
		else if (sq.isShaded())
			os << ".";
		else
			os << " ";

		return os;
	}

private:
	bool shaded;
	Piece* pieceHere;
};