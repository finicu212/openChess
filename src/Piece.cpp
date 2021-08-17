#pragma once
#include "Piece.h"

char Piece::art()
{
    return art_;
}

bool Piece::isWhite()
{
    return isWhite_;
}

Pos2D Piece::pos()
{
    return pos_;
}

void Piece::setPos(const Pos2D& p)
{
    pos_ = p;
}

void Piece::setHasMoved(bool m)
{
    hasMoved_ = m;
}

bool Piece::hasMoved()
{
    return hasMoved_;
}

Piece::Piece(char a, bool w) : art_(a), isWhite_(w) {};

Pawn::Pawn(bool isWhite) : Piece(isWhite ? 'P' : 'p', isWhite) {};

Rook::Rook(bool isWhite) : Piece(isWhite ? 'R' : 'r', isWhite) {};

Knight::Knight(bool isWhite) : Piece(isWhite ? 'N' : 'n', isWhite) {};

Bishop::Bishop(bool isWhite) : Piece(isWhite ? 'B' : 'b', isWhite) {};

Queen::Queen(bool isWhite) : Piece(isWhite ? 'Q' : 'q', isWhite) {};

King::King(bool isWhite) : Piece(isWhite ? 'K' : 'k', isWhite) {};

bool Pawn::isValidMove(const Move& move)
{
    Pos2D moveDelta = move.dest() - move.src();

    // basic moves
    if (move.intention() == 0)
    {
        // 1 square
        if (moveDelta == Pos2D(isWhite_ ? 1 : -1, 0))
        {
            return true;
        }

        // 2 squares
        if (moveDelta == Pos2D(isWhite_ ? 2 : -2, 0) && !hasMoved_)
        {
            return true;
        }
    }

    // capture move
    if (move.intention() == 1 &&
        (moveDelta.x == (isWhite_ ? 1 : -1)) &&
        ((moveDelta.y == 1) || (moveDelta.y == -1)))
    {
        return true;
    }

    return false;
}

bool Pawn::canPromote()
{
    return (pos_.x == 0 || pos_.x == 7);
}

bool Rook::isValidMove(const Move& move)
{
    // rook tried jumping over a piece
    if (move.intention() == 253)
        return false;

    Pos2D moveDelta = (move.dest() - move.src()).abs();
    return moveDelta.x == 0 || moveDelta.y == 0;
}

bool Knight::isValidMove(const Move& move)
{
    Pos2D moveDelta = (move.dest() - move.src()).abs();

    return (moveDelta.x == 1 && moveDelta.y == 2) || (moveDelta.x == 2 && moveDelta.y == 1);
}

bool Bishop::isValidMove(const Move& move)
{
    // bishop tried jumping over piece
    if (move.intention() == 254)
        return false;

    Pos2D moveDelta = (move.dest() - move.src()).abs();
    return (moveDelta.x == moveDelta.y);
}

bool Queen::isValidMove(const Move& move)
{
    // tried jumping over piece like a bishop or a rook
    if (move.intention() == 254 || move.intention() == 253)
        return false;

    Pos2D moveDelta = (move.dest() - move.src()).abs();
    return moveDelta.x == 0 || moveDelta.y == 0 || (moveDelta.x == moveDelta.y);
}

bool King::isValidMove(const Move& move)
{
    // is king castling?
    if (move.intention() == 2 || move.intention() == 3)
        return true;

    Pos2D moveDelta = (move.dest() - move.src()).abs();
    return moveDelta.x < 2 && moveDelta.y < 2;
}


bool Rook::canPromote()
{
    return false;
}

bool Knight::canPromote()
{
    return false;
}

bool Bishop::canPromote()
{
    return false;
}

bool Queen::canPromote()
{
    return false;
}

bool King::canPromote()
{
    return false;
}