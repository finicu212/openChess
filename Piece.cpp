#pragma once
#include "Piece.h"

char Piece::getArt()
{
	return art;
}

bool Piece::getColor()
{
	return isWhite;
}

void Piece::setPos(const Pos2D& p)
{
	pos = p;
}

void Piece::setHasMoved(bool m)
{
	hasMoved = m;
}

Piece::Piece(char a, bool w) : art(a), isWhite(w) {};

Pawn::Pawn(bool isWhite) : Piece(isWhite ? 'P' : 'p', isWhite) {};

Rook::Rook(bool isWhite) : Piece(isWhite ? 'R' : 'r', isWhite) {};

Knight::Knight(bool isWhite) : Piece(isWhite ? 'N' : 'n', isWhite) {};

Bishop::Bishop(bool isWhite) : Piece(isWhite ? 'B' : 'b', isWhite) {};

Queen::Queen(bool isWhite) : Piece(isWhite ? 'Q' : 'q', isWhite) {};

King::King(bool isWhite) : Piece(isWhite ? 'K' : 'k', isWhite) {};

bool Pawn::isValidMove(const Move& move)
{
	Pos2D moveDelta = move.dest() - move.src();

	// basic moves
	if (move.intention() == 0)
	{
		// 1 square
		if (moveDelta == Pos2D(isWhite ? 1 : -1, 0))
		{
			return true;
		}

		// 2 squares
		if (moveDelta == Pos2D(isWhite ? 2 : -2, 0) && !hasMoved)
		{
			return true;
		}
	}

	// capture move
	if (move.intention() == 1 &&
		(moveDelta.x == (isWhite ? 1 : -1)) &&
		((moveDelta.y == 1) || (moveDelta.y == -1)))
	{
		return true;
	}

	return false;
}

bool Pawn::canPromote()
{
	return (pos.x == 0 || pos.x == 7) && canPromote;
}

bool Rook::isValidMove(const Move& move)
{
	return false;
}

bool Knight::isValidMove(const Move& move)
{
	Pos2D moveDelta = (move.dest() - move.src()).abs();

	return (moveDelta.x == 1 && moveDelta.y == 2) || (moveDelta.x == 2 && moveDelta.y == 1);
}

bool Bishop::isValidMove(const Move& move)
{
	return false;
}

bool Queen::isValidMove(const Move& move)
{
	return false;
}

bool King::isValidMove(const Move& move)
{
	return false;
}


bool Rook::canPromote()
{
	return false;
}

bool Knight::canPromote()
{
	return false;
}

bool Bishop::canPromote()
{
	return false;
}

bool Queen::canPromote()
{
	return false;
}

bool King::canPromote()
{
	return false;
}