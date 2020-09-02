#include "Piece.h"
#pragma once

char Piece::getArt()
{
	return art;
}

void Piece::setPos(const Pos2D& p)
{
	pos = p;
}

Pawn::Pawn(bool isWhite) : Piece(isWhite ? 'P' : 'p') {};

Rook::Rook(bool isWhite) : Piece(isWhite ? 'R' : 'r') {};

Knight::Knight(bool isWhite) : Piece(isWhite ? 'N' : 'n') {};

Bishop::Bishop(bool isWhite) : Piece(isWhite ? 'B' : 'b') {};

Queen::Queen(bool isWhite) : Piece(isWhite ? 'Q' : 'q') {};

King::King(bool isWhite) : Piece(isWhite ? 'K' : 'k') {};