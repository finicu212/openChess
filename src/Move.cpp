#include "Move.h"

Move::Move() {};

Move::Move(const Pos2D& org, const Pos2D& destination) : src_(org), dest_(destination) {}

bool Move::outOfBounds(const Move& move)
{
    return (Pos2D::outOfBounds(move.src_) || Pos2D::outOfBounds(move.dest_));
}

Pos2D Move::src() const
{
    return src_;
}

Pos2D Move::dest() const
{
    return dest_;
}

uint8_t Move::intention() const
{
    return intention_;
}

void Move::setIntention(uint8_t intent)
{
    intention_ = intent;
}

Move Move::getMove(const std::string& s, const std::string& d)
{
    Move newMove;
    newMove.src_ = Pos2D::getPos2D(s);
    newMove.dest_ = Pos2D::getPos2D(d);

    return newMove;
}