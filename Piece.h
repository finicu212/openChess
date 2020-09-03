#pragma once
#include <string>
#include "Move.h"

class Piece
{
public:
	char getArt();

	bool getColor();

	void setPos(const Pos2D& p);

	void setHasMoved(bool m);

	virtual bool isValidMove(const Move& move) = 0;

	Piece(char a, bool w);

protected:
	char art;
	bool isWhite, hasMoved = false;
	Pos2D pos;
};

class Pawn : public Piece
{
public:
	Pawn(bool isWhite);

	bool isValidMove(const Move& move) override;
};

class Rook : public Piece
{
public:
	Rook(bool isWhite);

	bool isValidMove(const Move& move) override;
};

class Knight : public Piece
{
public:
	Knight(bool isWhite);

	bool isValidMove(const Move& move) override;
};

class Bishop : public Piece
{
public:
	Bishop(bool isWhite);

	bool isValidMove(const Move& move) override;
};

class Queen : public Piece
{
public:
	Queen(bool isWhite);

	bool isValidMove(const Move& move) override;
};

class King : public Piece
{
public:
	King(bool isWhite);

	bool isValidMove(const Move& move) override;
};