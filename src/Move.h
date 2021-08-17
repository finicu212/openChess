#pragma once
#include <iostream>
#include "Pos2D.h"

class Move
{
public:
    Move();

    Move(const Pos2D& org, const Pos2D& destination);

    static bool outOfBounds(const Move& move);

    /// <summary>
    /// Takes two strings and outputs readable data
    /// </summary>
    /// <param name="s"> - string that represents the origin square (ex: "e2")</param>
    /// <param name="d"> - string that represents the destination square (ex: "e4")</param>
    /// <returns>a Move object</returns>
    static Move getMove(const std::string& s, const std::string& d);

    Pos2D src() const;

    Pos2D dest() const;

    uint8_t intention() const;

    void setIntention(uint8_t intent);

private:
    Pos2D src_, dest_;
    uint8_t intention_ = 255;
    /*
    *    Table of intentions:
    *
    *    0 - Standard, no capture move
    *    1 - Capturing move
    *    2 - Castling kingside
    *    3 - Castling queenside
    *    4 - En passant capture
    *
    *    Possible invalid moves:
    *    253 - Tried jumping over a piece with a rook (or queen, double square initial pawn move)
    *    254 - Tried jumping over a piece with a bishop (or queen)
    *    255 - Invalid move (to be checked in Board::isValidMove)
    */
};