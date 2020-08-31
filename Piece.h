#pragma once
#include <string>
#include "Move.h"

extern Board g_board;

class Piece
{
public:
	char getArt();

	void setPos(const Pos2D& p);

	virtual bool isValidMove(const Move& move) = 0;

	Piece(char a) : art(a) {};

private:
	char art;
	Pos2D pos;
};

class Pawn : public Piece
{
public:
	Pawn(bool isWhite);

	bool isValidMove(const Move& move) override;

private:
	bool hasMoved;
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