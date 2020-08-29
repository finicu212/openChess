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

// ------- PAWN:

Pawn::Pawn(bool isWhite) : Piece(isWhite ? 'P' : 'p') {};

bool Pawn::isValidMove(const Move& move)
{
	return false;
}

// ------- ROOK:

Rook::Rook(bool isWhite) : Piece(isWhite ? 'R' : 'r') {};

bool Rook::isValidMove(const Move& move)
{
	return false;
}

// ------- KNIGHT:

Knight::Knight(bool isWhite) : Piece(isWhite ? 'N' : 'n') {};

bool Knight::isValidMove(const Move& move)
{
	return false;
}

// ------- BISHOP:

Bishop::Bishop(bool isWhite) : Piece(isWhite ? 'B' : 'b') {};

bool Bishop::isValidMove(const Move& move)
{
	return false;
}

// ------- QUEEN:

Queen::Queen(bool isWhite) : Piece(isWhite ? 'Q' : 'q') {};

bool Queen::isValidMove(const Move& move)
{
	return false;
}

// ------- KING:

King::King(bool isWhite) : Piece(isWhite ? 'K' : 'k') {};

bool King::isValidMove(const Move& move)
{
	return false;
}