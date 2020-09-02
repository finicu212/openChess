#pragma once
#include <iostream>

extern bool g_playingAsWhite;

struct Pos2D
{
	uint8_t x, y;

	static Pos2D getPos2D(const std::string& posString);

	Pos2D abs();

	Pos2D operator-(const Pos2D& pos);

	bool operator==(const Pos2D& pos);
};

class Move
{
public:
	Move();
	Move(const Pos2D& org, const Pos2D& destination);

	/// <summary>
	/// Takes two strings and outputs readable data
	/// </summary>
	/// <param name="s"> - string that represents the origin square (ex: "e2")</param>
	/// <param name="d"> - string that represents the destination square (ex: "e4")</param>
	/// <returns>a Move object</returns>
	static Move getMove(const std::string& s, const std::string& d);

	Move invert() const;

	Pos2D src() const;

	Pos2D dest() const;

private:
	Pos2D src_, dest_;
};