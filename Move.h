#pragma once
#include <iostream>

struct Pos2D
{
	uint8_t x, y;
};

class Move
{
public:
	Move();
	Move(Pos2D org, Pos2D destination);

private:
	Pos2D src, dest;
};

Move::Move() {};

Move::Move(Pos2D org, Pos2D destination) : src(org), dest(destination) {}
