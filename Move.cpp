#include "Move.h"

Move::Move() {};

Move::Move(Pos2D org, Pos2D destination) : src_(org), dest_(destination) {}

Pos2D Move::src() const
{
	return src_;
}

Pos2D Move::dest() const
{
	return dest_;
}

Move Move::makeMove(std::string s, std::string d)
{
	Move newMove;
	newMove.src_.x = tolower(s[0]) - 'a';
	newMove.src_.y = s[1] - 49;

	newMove.dest_.x = tolower(d[0]) - 'a';
	newMove.dest_.y = d[1] - 49;

	return newMove;
}