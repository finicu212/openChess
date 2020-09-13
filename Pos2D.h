#pragma once
#include <iostream>

struct Pos2D
{
	int8_t x, y;

	Pos2D();

	Pos2D(int8_t x, int8_t y);

	static bool outOfBounds(const Pos2D& pos);

	static Pos2D getPos2D(const std::string& posString);

	Pos2D abs();

	bool operator==(const Pos2D& pos);

	Pos2D operator-(const Pos2D& pos);

	Pos2D operator+(const Pos2D& pos);
};