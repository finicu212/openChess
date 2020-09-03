#pragma once
#include "Board.h"
// including Board.h to reference global variable g_board which is of type Board

char Piece::getArt()
{
	return art;
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


extern Board g_board;

bool Pawn::isValidMove(const Move& move)
{
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