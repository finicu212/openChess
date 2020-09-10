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

	void setPlayingAsWhite(bool asWhite);

	bool playingAsWhite();

	bool whitesTurn();

	uint8_t findIntention(const Move& move);

	uint8_t gameOver();

	Board();

	friend std::ostream& operator<<(std::ostream& os, const Board& b);

private:
	vector<vector<shared_ptr<Piece>>> board_;
	vector<shared_ptr<Piece>> whitePieces_, blackPieces_;
	shared_ptr<King> whiteKing, blackKing;
	bool playingAsWhite_ = true, whitesTurn_ = true;;
};