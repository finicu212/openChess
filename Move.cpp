#include "Move.h"

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