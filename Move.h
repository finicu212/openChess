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

	/// <summary>
	/// Takes two strings and outputs readable data
	/// </summary>
	/// <param name="s"> - string that represents the origin square (ex: "e2")</param>
	/// <param name="d"> - string that represents the destination square (ex: "e4")</param>
	/// <returns>a Move object</returns>
	static Move makeMove(std::string s, std::string d);

private:
	Pos2D src, dest;
};

Move::Move() {};

Move::Move(Pos2D org, Pos2D destination) : src(org), dest(destination) {}

Move Move::makeMove(std::string s, std::string d)
{
	Move newMove;
	newMove.src.x = tolower(s[0]) - 'a';
	newMove.src.y = s[1] - 49;

	newMove.dest.x = tolower(d[0]) - 'a';
	newMove.dest.y = d[1] - 49;

	return newMove;
}
