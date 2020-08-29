#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "Piece.h"

using std::vector;
using std::make_shared;
using std::shared_ptr;

class Board
{
public:
	shared_ptr<Piece> pieceAt(int i, int j) const;

	char getArtAt(int i, int j) const;

	void movePiece(const Move& move, const shared_ptr<Piece>& piece);

	Board(bool playingAsWhite);

	friend std::ostream& operator<<(std::ostream& os, const Board& b);

private:
	bool whiteSide;
	vector<vector<shared_ptr<Piece>>> board;
};