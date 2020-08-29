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

	Pos2D src();

	Pos2D dest();

private:
	Pos2D src_, dest_;
};

Move::Move() {};

Move::Move(Pos2D org, Pos2D destination) : src_(org), dest_(destination) {}

Pos2D Move::src()
{ 
	return src_; 
}

Pos2D Move::dest()
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