#include "Board.h"
#include "Color.h"
#include <string>

shared_ptr<Piece> Board::pieceAt(const Pos2D& pos) const
{
    return board_[pos.x][pos.y];
}

void Board::setPiece(const Pos2D& pos, const shared_ptr<Piece>& piece)
{
    board_[pos.x][pos.y] = piece;

    if (piece != nullptr)
    {
        piece->setPos(pos);
        piece->setHasMoved(true);
    }
}

shared_ptr<King> Board::king(bool coloredWhite)
{
    if (coloredWhite)
        return whiteKing_;

    return blackKing_;
}

vector<shared_ptr<Piece>> Board::pieces(bool coloredWhite)
{
    if (coloredWhite)
        return whitePieces_;

    return blackPieces_;
}

void Board::addPiece(const shared_ptr<Piece>& piece)
{
    if (piece == nullptr)
        return;

    if (piece->isWhite())
        whitePieces_.push_back(piece);
    else
        blackPieces_.push_back(piece);
}

void Board::delPiece(const shared_ptr<Piece>& piece)
{
    if (piece == nullptr)
        return;

    if (piece->isWhite())
        for (uint8_t i = 0; i < whitePieces_.size(); i++)
        {
            if (whitePieces_[i] == piece)
            {
                whitePieces_.erase(whitePieces_.begin() + i);
            }
        }
    else
        for (uint8_t i = 0; i < blackPieces_.size(); i++)
        {
            if (blackPieces_[i] == piece)
            {
                blackPieces_.erase(blackPieces_.begin() + i);
            }
        }
}

std::string Board::getArtAt(const Pos2D& pos) const
{
    shared_ptr<Piece> pHere = pieceAt(pos);

    // if i + j is even, then it's a shaded square
    bool isShadedSquare = (pos.x + pos.y) % 2 == 0;
    std::string c;
    c += isShadedSquare ? black_bg_ : white_bg_;

    // no piece here
    if (pHere == nullptr)
    {
        return c += "   " + Color::end();
    }

    if (pHere->isWhite() && isShadedSquare)
        c += white_black_bg_;
    else if (pHere->isWhite())
        c += white_white_bg_;

    c += " " + std::string(1, pHere->art()) + " " + Color::end();
    return c;
}

shared_ptr<Piece> Board::kingInCheck(bool col)
{
    whitesTurn_ = !whitesTurn_;
    for (shared_ptr<Piece> p : pieces(!col))
    {
        Move checkMove(p->pos(), king(col)->pos());
        checkMove.setIntention(findIntention(checkMove));
        if (isValidMove(checkMove))
        {
            whitesTurn_ = !whitesTurn_;
            return p;
        }
    }

    whitesTurn_ = !whitesTurn_;
    return nullptr;
}

void Board::movePiece(const Move& move)
{
    shared_ptr<Piece> pieceHere = pieceAt(move.src());
    shared_ptr<Piece> pieceThere = pieceAt(move.dest());

    // reference there
    setPiece(move.dest(), pieceHere);

    // remove piece from here
    setPiece(move.src(), nullptr);

    // remove from our vectors if we captured
    delPiece(pieceThere);

    //            --- SPECIAL MOVES ---
    // Pawn promotion
    if (pieceHere->canPromote())
    {
        shared_ptr<Piece> promotedPiece = make_shared<Queen>(pieceHere->isWhite());
        setPiece(move.dest(), promotedPiece);

        delPiece(pieceHere);
        addPiece(promotedPiece);
    }

    // Castling
    if (move.intention() == 2 || move.intention() == 3)
    {
        shared_ptr<Piece> targetRook = board_[pieceHere->isWhite() ? 0 : 7][move.intention() == 3 ? 0 : 7];
        setPiece(targetRook->pos(), nullptr);
        setPiece(move.dest() + Pos2D(0, move.intention() == 3 ? 1 : -1), targetRook);
    }

    whitesTurn_ = !whitesTurn_;
}

bool Board::isValidMove(const Move& move)
{
    if (move.intention() == 255)
        return false;

    shared_ptr<Piece> pieceHere = pieceAt(move.src());
    shared_ptr<Piece> pieceThere = pieceAt(move.dest());

    bool pieceColor = pieceHere->isWhite();

    if (pieceColor != whitesTurn_)
        return false;

    if (!pieceAt(move.src())->isValidMove(move))
        return false;

    if (kingInCheck(pieceColor) != nullptr)
    {
        // try the move, see if we're still in check afterwards
        setPiece(move.dest(), pieceHere);
        setPiece(move.src(), nullptr);

        bool inCheck = (kingInCheck(pieceColor) != nullptr);
        setPiece(move.src(), pieceHere);
        setPiece(move.dest(), pieceThere);

        if (inCheck)
            return false;
    }

    return true;
}

void Board::setPlayingAsWhite(bool asWhite)
{
    playingAsWhite_ = asWhite;
}

bool Board::playingAsWhite()
{
    return playingAsWhite_;
}

bool Board::whitesTurn()
{
    return whitesTurn_;
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

uint8_t Board::findIntention(const Move& move)
{
    Pos2D moveDelta = move.dest() - move.src();
    shared_ptr<Piece> pieceHere = pieceAt(move.src());

    // can't move empty squares
    if (pieceHere == nullptr)
        return 255;

    // --- CASTLING ---

    if ((pieceHere == whiteKing_ || pieceHere == blackKing_) &&
        (moveDelta.abs() == Pos2D(0, 2)) &&
        (!pieceHere->hasMoved()))
    {
        bool validCastle = true;
        shared_ptr<Piece> targetRook;
        targetRook = board_[pieceHere->isWhite() ? 0 : 7][moveDelta.y < 0 ? 0 : 7];

        if (targetRook->hasMoved())
        {
            validCastle = false;
        }

        // make sure no pieces are in the way
        Pos2D distRook = targetRook->pos() - pieceHere->pos();

        for (int i = sgn(distRook.y); abs(i) < abs(distRook.y); i += sgn(distRook.y))
        {
            if (board_[move.src().x][move.src().y + i] != nullptr)
            {
                validCastle = false;
            }
        }

        // make sure no enemy piece is looking between (or at) king & rook. ~EXPENSIVE!
        for (int i = 0; abs(i) < (abs(distRook.y) + 1); i += sgn(distRook.y))
        {
            Pos2D posHere = Pos2D(move.src().x, move.src().y + i);
            for (auto p : pieces(!pieceHere->isWhite()))
            {
                if (isValidMove(Move(p->pos(), posHere)))
                {
                    validCastle = false;
                }
            }
        }

        if (validCastle)
        {
            if (distRook.y == 3)
                return 2; // kingside
            else
                return 3; // queenside
        }
    }

    /// --- PIECE JUMPING --- 

    // bishop-like movement
    if (moveDelta.x == moveDelta.y)
    {
        // TODO: make a method or something to make this thing readable
        // (its a for loop that goes the direction of the delta)
        for (int i = sgn(moveDelta.x); abs(i) < abs(moveDelta.x); i += sgn(moveDelta.x))
        {
            if (board_[move.src().x + i][move.src().y + i] != nullptr)
            {
                return 254; // trying to jump over a piece with a bishop
            }
        }
    }

    // rook-like movement
    if (moveDelta.x == 0)
    {
        for (int i = sgn(moveDelta.y); abs(i) < abs(moveDelta.y); i += sgn(moveDelta.y))
        {
            if (board_[move.src().x][move.src().y + i] != nullptr)
            {
                return 253; // trying to jump over a piece with a rook (y axis)
            }
        }
    }
    else if (moveDelta.y == 0) // double square initial pawn move is also prevented from jumping pieces here
    {
        for (int i = sgn(moveDelta.x); abs(i) < abs(moveDelta.x); i += sgn(moveDelta.x))
        {
            if (board_[move.src().x + i][move.src().y] != nullptr)
            {
                return 253; // trying to jump over a piece with a rook (x axis)
            }
        }
    }

    // --- SIMPLE MOVES ---

    if (pieceAt(move.dest()) == nullptr)
        return 0; // standard move

    if (pieceHere->isWhite() != pieceAt(move.dest())->isWhite())
        return 1; // capturing move

    return 255; // invalid move

    // TODO: 4 for en passant pawn capture.
}

bool Board::canBlock(const Move& moveToBlock, const shared_ptr<Piece>& blocker)
{
    Move captureMove = Move(blocker->pos(), moveToBlock.src());
    captureMove.setIntention(findIntention(captureMove));
    if (isValidMove(captureMove))
    {
        // can just capture the target
        return true;
    }

    Pos2D attackerMoveDelta = moveToBlock.dest() - moveToBlock.src();

    if (attackerMoveDelta.x == attackerMoveDelta.y)
    {
        // we're trying to block a bishop here
        for (int i = sgn(attackerMoveDelta.x); abs(i) < abs(attackerMoveDelta.x); i += sgn(attackerMoveDelta.x))
        {
            Pos2D blockedSquare(moveToBlock.dest().x - i, moveToBlock.dest().y - i);
            Move blockingMove = Move(blocker->pos(), blockedSquare);
            blockingMove.setIntention(findIntention(blockingMove));

            if (isValidMove(blockingMove))
            {
                return true;
            }
        }
    }

    if (attackerMoveDelta.x == 0)
    {
        // we're trying to block a vertical rook-like attack here
        for (int i = sgn(attackerMoveDelta.y); abs(i) < abs(attackerMoveDelta.y); i += sgn(attackerMoveDelta.y))
        {
            Pos2D blockedSquare(moveToBlock.dest().x, moveToBlock.dest().y + i);
            Move blockingMove = Move(blocker->pos(), blockedSquare);
            blockingMove.setIntention(findIntention(blockingMove));

            if (isValidMove(blockingMove))
            {
                return true;
            }
        }
    }

    if (attackerMoveDelta.y == 0)
    {
        // we're trying to block a horizontal rook-like attack here
        for (int i = sgn(attackerMoveDelta.x); abs(i) < abs(attackerMoveDelta.x); i += sgn(attackerMoveDelta.x))
        {
            Pos2D blockedSquare(moveToBlock.dest().x + i, moveToBlock.dest().y);
            Move blockingMove = Move(blocker->pos(), blockedSquare);
            blockingMove.setIntention(findIntention(blockingMove));

            if (isValidMove(blockingMove))
            {
                return true;
            }
        }
    }

    return false;
}

uint8_t Board::gameOver()
{
    shared_ptr<Piece> attacker = kingInCheck(whitesTurn_);

    // in check
    if (attacker != nullptr)
    {
        bool checkMate = true;

        // can run with king?
        for (int8_t dx = -1; dx <= 1; dx++)
        {
            for (int8_t dy = -1; dy <= 1; dy++)
            {
                Pos2D kingPos = king(whitesTurn_)->pos();
                Pos2D runPos = Pos2D(dx, dy) + kingPos;

                // out of bounds
                if (runPos.x < 0 || runPos.x > 7 || runPos.y < 0 || runPos.y > 7)
                    continue;

                Move runMove = Move(kingPos, runPos);
                runMove.setIntention(findIntention(runMove));
                if (isValidMove(runMove))
                {
                    checkMate = false;
                    break;
                }
            }
        }

        if (checkMate)
        {
            // go through all pieces and see if we can block the check.
            // Expensive, so only do this if cant run with king

            for (shared_ptr<Piece> p : pieces(whitesTurn_))
            {
                if (canBlock(Move(attacker->pos(), king(whitesTurn_)->pos()), p))
                {
                    checkMate = false;
                    break;
                }
            }
        }

        if (checkMate)
            return 1;
    }


    return 0;
}

Board::Board()
{
    // initialize the board_ with nullptrs
    board_.resize(8);
    for (uint8_t i = 0; i < 8; i++)
    {
        board_[i].resize(8, nullptr);
    }

    // white major pieces
    board_[0][0] = make_shared<Rook>(true);
    board_[0][1] = make_shared<Knight>(true);
    board_[0][2] = make_shared<Bishop>(true);
    board_[0][3] = make_shared<Queen>(true);
    board_[0][4] = whiteKing_ = make_shared<King>(true);
    board_[0][5] = make_shared<Bishop>(true);
    board_[0][6] = make_shared<Knight>(true);
    board_[0][7] = make_shared<Rook>(true);

    // white pawns
    for (uint8_t i = 0; i < 8; i++)
    {
        board_[1][i] = make_shared<Pawn>(true);
    }

    // black pawns
    for (uint8_t i = 0; i < 8; i++)
    {
        board_[6][i] = make_shared<Pawn>(false);
    }

    // black major pieces
    board_[7][0] = make_shared<Rook>(false);
    board_[7][1] = make_shared<Knight>(false);
    board_[7][2] = make_shared<Bishop>(false);
    board_[7][3] = make_shared<Queen>(false);
    board_[7][4] = blackKing_ = make_shared<King>(false);
    board_[7][5] = make_shared<Bishop>(false);
    board_[7][6] = make_shared<Knight>(false);
    board_[7][7] = make_shared<Rook>(false);

    // tell each piece what square they're on
    for (int8_t i = 0; i < 8; i++)
    {
        for (int8_t j = 0; j < 8; j++)
        {
            if (board_[i][j] != nullptr)
            {
                board_[i][j]->setPos({ i, j });

                addPiece(board_[i][j]);
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
    os << "\n   A  B  C  D  E  F  G  H\n";

    for (uint8_t i = 0; i < 8; i++)
    {
        int currIndex = b.playingAsWhite_ ? (8 - i) : (i + 1);
        os << currIndex << " ";

        for (uint8_t j = 0; j < 8; j++)
        {
            std::string art = b.getArtAt(Pos2D(b.playingAsWhite_ ? (7 - i) : i, j));
            os << art;
        }

        os << " " << currIndex << '\n';
    }
    os << "   A  B  C  D  E  F  G  H\n";

    return os;
}