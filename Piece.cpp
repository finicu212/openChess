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

	if (move.intention() == 0 &&
		moveDelta == Pos2D(isWhite ? 1 : -1, 0))
	{
		return true;
	}

	if (move.intention() == 0 &&
		moveDelta.x == isWhite ? 1 : -1 &&
		abs(moveDelta.y) == 1)
	{
		return true;
	}

	return false;
}

bool Rook::isValidMove(const Move& move)
{
	return false;
}

bool Knight::isValidMove(const Move& move)
{
	return false;
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