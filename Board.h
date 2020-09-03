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
	shared_ptr<Piece> pieceAt(const Pos2D& pos) const;

	void setPiece(const Pos2D& pos, const shared_ptr<Piece>& piece);

	char getArtAt(const Pos2D& pos) const;

	void movePiece(const Move& move);

	bool isValidMove(const Move& move);

	void setPlayingPerspective(bool asWhite);

	bool getPerspective();

	uint8_t getIntention(const Move& move);

	Board();

	friend std::ostream& operator<<(std::ostream& os, const Board& b);

private:
	vector<vector<shared_ptr<Piece>>> board;
	bool playingAsWhite = true;
};