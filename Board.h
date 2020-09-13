#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Piece.h"
#include "Color.h"

using std::vector;
using std::make_shared;
using std::shared_ptr;

class Board
{
public:
	shared_ptr<Piece> pieceAt(const Pos2D& pos) const;

	shared_ptr<King> king(bool coloredWhite);

	vector<shared_ptr<Piece>> pieces(bool coloredWhite);

	void delPiece(const shared_ptr<Piece>& piece);

	void setPiece(const Pos2D& pos, const shared_ptr<Piece>& piece);

	std::string getArtAt(const Pos2D& pos) const;

	// returns piece that attacks king
	shared_ptr<Piece> kingInCheck(bool col);

	void movePiece(const Move& move);

	bool isValidMove(const Move& move);

	void setPlayingAsWhite(bool asWhite);

	bool playingAsWhite();

	bool whitesTurn();

	uint8_t findIntention(const Move& move);

	bool canBlock(shared_ptr<Piece> target, shared_ptr<Piece> blocker, Pos2D posToBlock);

	uint8_t gameOver();

	Board();

	friend std::ostream& operator<<(std::ostream& os, const Board& b);

private:
	vector<vector<shared_ptr<Piece>>> board_;
	vector<shared_ptr<Piece>> whitePieces_, blackPieces_;
	shared_ptr<King> whiteKing_, blackKing_;
	bool playingAsWhite_ = true, whitesTurn_ = true;

	const std::string white_bg_ = Color::ANSI(Color::FG_BLUE, Color::BG_WHITE, false);
	const std::string black_bg_ = Color::ANSI(Color::FG_BLUE, Color::BG_GRAY, false);

	const std::string white_white_bg_ = Color::ANSI(Color::FG_GRAY, Color::BG_WHITE, false);
	const std::string white_black_bg_ = Color::ANSI(Color::FG_WHITE, Color::BG_GRAY, false);
};
