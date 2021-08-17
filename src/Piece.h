#pragma once
#include <string>
#include "Move.h"

class Piece
{
public:
    // getter for the character art
    char art();

    // getter for piece color
    bool isWhite();

    // getter for piece position
    Pos2D pos();

    // setter for piece position
    void setPos(const Pos2D& p);

    // getter for whether or not piece has moved
    bool hasMoved();

    // setter for whether or not piece has moved
    void setHasMoved(bool m);

    // abstract method that checks if given move is valid.
    // uses move::intention to figure out if jumping pieces, or moving in a weird fashion
    virtual bool isValidMove(const Move& move) = 0;

    virtual bool canPromote() = 0;

    Piece(char a, bool w);

protected:
    char art_;
    bool isWhite_, hasMoved_ = false;
    Pos2D pos_;
};

class Pawn : public Piece
{
public:
    Pawn(bool isWhite);

    bool isValidMove(const Move& move) override;

    bool canPromote() override;
};

class Rook : public Piece
{
public:
    Rook(bool isWhite);

    bool isValidMove(const Move& move) override;

    bool canPromote() override;
};

class Knight : public Piece
{
public:
    Knight(bool isWhite);

    bool isValidMove(const Move& move) override;

    bool canPromote() override;
};

class Bishop : public Piece
{
public:
    Bishop(bool isWhite);

    bool isValidMove(const Move& move) override;

    bool canPromote() override;
};

class Queen : public Piece
{
public:
    Queen(bool isWhite);

    bool isValidMove(const Move& move) override;

    bool canPromote() override;
};

class King : public Piece
{
public:
    King(bool isWhite);

    bool isValidMove(const Move& move) override;

    bool canPromote() override;
};