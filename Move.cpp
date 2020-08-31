#include "Move.h"

Pos2D Pos2D::getPos2D(const std::string& posString)
{
	Pos2D newPos;
	newPos.y = tolower(posString[0]) - 'a';
	newPos.x = posString[1] - 49;

	// MAYBE REVERSE x AND y
	return newPos;
}

Move::Move() {};

Move::Move(const Pos2D& org, const Pos2D& destination) : src_(org), dest_(destination) {}

Pos2D Move::src() const
{
	return src_;
}

Pos2D Move::dest() const
{
	return dest_;
}

Move Move::getMove(const std::string& s, const std::string& d)
{
	Move newMove;
	newMove.src_ = Pos2D::getPos2D(s);
	newMove.dest_ = Pos2D::getPos2D(d);

	return newMove;
}

Move Move::invert() const
{
	Move newMove = *this;
	newMove.src_.x = abs(src_.x + (3.5 - src_.x) * 2);
	newMove.dest_.x = abs(dest_.x + (3.5 - dest_.x) * 2);
	return newMove;
}	