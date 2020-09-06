#pragma once
#include <string>
#include "Move.h"

class Piece
{
public:
	char art();

	bool isWhite();

	Pos2D pos();

	void setPos(const Pos2D& p);

	void setHasMoved(bool m);

	virtual bool isValidMove(const Move& move) = 0;

	virtual bool canPromote() = 0;

	Piece(char a, bool w);

protected:
	char art_;
	bool isWhite_, hasMoved_ = false;
	Pos2D pos_;
};

class Pawn : public Piece
{
public:
	Pawn(bool isWhite);

	bool isValidMove(const Move& move) override;

	bool canPromote() override;
};

class Rook : public Piece
{
public:
	Rook(bool isWhite);

	bool isValidMove(const Move& move) override;

	bool canPromote() override;
};

class Knight : public Piece
{
public:
	Knight(bool isWhite);

	bool isValidMove(const Move& move) override;

	bool canPromote() override;
};

class Bishop : public Piece
{
public:
	Bishop(bool isWhite);

	bool isValidMove(const Move& move) override;

	bool canPromote() override;
};

class Queen : public Piece
{
public:
	Queen(bool isWhite);

	bool isValidMove(const Move& move) override;

	bool canPromote() override;
};

class King : public Piece
{
public:
	King(bool isWhite);

	bool isValidMove(const Move& move) override;

	bool canPromote() override;
};