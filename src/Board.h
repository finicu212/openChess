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
    // getter for piece (can be nullptr) based on pair of coordinates
    shared_ptr<Piece> pieceAt(const Pos2D& pos) const;

    // updates board_ using piece at given coords
    // updates piece::pos and piece::hasMoved if not nullptr
    void setPiece(const Pos2D& pos, const shared_ptr<Piece>& piece);

    // getter for white/black king
    shared_ptr<King> king(bool coloredWhite);

    // getter for white/black vec of pieces
    vector<shared_ptr<Piece>> pieces(bool coloredWhite);

    // setter for perspective
    void setPlayingAsWhite(bool asWhite);

    // getter for perspective
    bool playingAsWhite();

    // getter for player turn
    bool whitesTurn();

    // add this piece to white/black vec of pieces (nullptr is not added)
    void addPiece(const shared_ptr<Piece>& piece);

    // remove this piece from white/black vec of pieces
    void delPiece(const shared_ptr<Piece>& piece);

    // get art (std::string art of piece), including color, at given coordinates. handles square shading
    std::string getArtAt(const Pos2D& pos) const;

    // returns piece that attacks king. returns nullptr if king not attacked
    shared_ptr<Piece> kingInCheck(bool col);

    // uses setPiece to execute move. cycles turns when move complete. checks if we're doing pawn promotion or castling
    // (TODO: ISSUE #43)
    void movePiece(const Move& move);

    // makes sure the current move is valid (to be used in main() before calling movePiece())
    // - generic invalid move (intention 255)
    // - moving pieces of whose turn it is
    // - see if the piece's move is valid (piece::isValidMove())
    // - king wont be in check after move
    bool isValidMove(const Move& move);

    // find the type of move we're trying to make.
    // 0    - standard move
    // 1    - capture move
    // 2    - kingside castle
    // 3    - queenside castle
    // 253    - piece jumping, vertical / horizontal (could be invalid)
    // 254    - piece jumping, bishop-like (could be invalid)
    // 255    - invalid move
    uint8_t findIntention(const Move& move);

    // check if blocker piece can capture target, or has a valid move between target and posToBlock. 
    bool canBlock(const Move& moveToBlock, const shared_ptr<Piece>& blocker);

    // find reason the game ended.
    // 0 - game still ongoing
    // 1 - checkmate
    // 2 - stalemate (no moves left for one player) TODO
    // 3 - stalemate (not enough material on board) TODO
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
