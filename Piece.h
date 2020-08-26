#pragma once
#include <string>

class Piece
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Piece& p)
	{
		os << p.art;
		return os;
	}

public:
	char art = 'p';
};

using Pawn = Piece;