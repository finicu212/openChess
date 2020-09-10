#include "Board.h"

shared_ptr<Piece> Board::pieceAt(const Pos2D& pos) const
{
	return board_[pos.x][pos.y];
}

void Board::setPiece(const Pos2D& pos, const shared_ptr<Piece>& piece)
{
	board_[pos.x][pos.y] = piece;
}

char Board::getArtAt(const Pos2D& pos) const
{
	shared_ptr<Piece> pHere = pieceAt(pos);

	// no piece here
	if (pHere == nullptr)
	{
		// if i + j is even, then it's a shaded square
		bool isShadedSquare = (pos.x + pos.y) % 2 == 0;

		// print . if it's shaded
		return isShadedSquare ? '.' : ' ';
	}

	return pHere->art();
}

void Board::movePiece(const Move& move)
{
	shared_ptr<Piece> pieceHere = pieceAt(move.src());
	shared_ptr<Piece> pieceThere = pieceAt(move.dest());
	// tell the piece where it will be
	pieceHere->setPos(move.dest());
	pieceHere->setHasMoved(true);

	// reference there
	setPiece(move.dest(), pieceHere);

	// remove piece from here
	setPiece(move.src(), nullptr);

	// remove from our vectors if we captured
	if (pieceThere != nullptr)
		if (pieceThere->isWhite())
			for (uint8_t i = 0; i < whitePieces_.size(); i++)
			{
				if (whitePieces_[i] == pieceThere)
				{
					whitePieces_.erase(whitePieces_.begin() + i);
				}
			}
		else
			for (uint8_t i = 0; i < blackPieces_.size(); i++)
			{
				if (blackPieces_[i] == pieceThere)
				{
					blackPieces_.erase(blackPieces_.begin() + i);
				}
			}

	//			--- SPECIAL MOVES ---
	// Pawn promotion
	if (pieceHere->canPromote())
	{
		pieceHere = make_shared<Queen>(pieceHere->isWhite());
	}

	// Castling
	if (move.intention() == 2 || move.intention() == 3)
	{
		std::cout << "board::castling\n";
		shared_ptr<Piece> targetRook = board_[pieceHere->isWhite() ? 0 : 7][move.intention() == 3 ? 0 : 7];
		setPiece(targetRook->pos(), nullptr);
		targetRook->setPos(move.dest() + Pos2D(0, move.intention() == 3 ? 1 : -1));
		setPiece(targetRook->pos(), targetRook);
	}
	
	whitesTurn_ = !whitesTurn_;
}

bool Board::isValidMove(const Move& move)
{
	if (move.intention() == 255)
		return false;

	if (pieceAt(move.src())->isWhite() != whitesTurn_)
		return false;
	
	return pieceAt(move.src())->isValidMove(move);
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

	// is castling?
	if ((pieceHere == whiteKing || pieceHere == blackKing) &&
		(moveDelta.abs() == Pos2D(0, 2)) &&
		(!pieceHere->hasMoved()))
	{
		std::cout << "castle candidate..\n";
		bool validCastle = true;
		shared_ptr<Piece> targetRook;
		targetRook = board_[pieceHere->isWhite() ? 0 : 7][moveDelta.y < 0 ? 0 : 7];

		if (targetRook->hasMoved())
		{
			std::cout << "failed castle: rook has moved\n";
			validCastle = false;
		}

		// make sure no pieces are in the way
		Pos2D distRook = targetRook->pos() - pieceHere->pos();

		for (int i = sgn(distRook.y); abs(i) < abs(distRook.y); i += sgn(distRook.y))
		{
			if (board_[move.src().x][move.src().y + i] != nullptr)
			{
				std::cout << "piece in the way\n";
				validCastle = false;
			}
		}

		// make sure no enemy piece is looking between (or at) king & rook. ~EXPENSIVE!
		for (int i = 0; abs(i) < (abs(distRook.y) + 1); i += sgn(distRook.y))
		{
			Pos2D posHere = Pos2D(move.src().x, move.src().y + i);
			if (pieceHere->isWhite())
			{
				for (auto p : blackPieces_)
				{
					if (isValidMove(Move(p->pos(), posHere)))
					{
						std::cout << p->art() << " black piece looking between\n";
						validCastle = false;
					}
				}
			}
			else
			{
				for (auto p : whitePieces_)
				{
					if (isValidMove(Move(p->pos(), posHere)))
					{
						std::cout << p->art() << " white piece looking between\n";
						validCastle = false;
					}
				}
			}
		}

		if (validCastle)
		{
			std::cout << "successful\n";
			if (distRook.y == 3)
				return 2; // kingside
			else
				return 3; // queenside
		}
	}

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

	if (pieceAt(move.dest()) == nullptr)
		return 0; // standard move

	// can't move on friendly pieces
	if (pieceHere->isWhite() == pieceAt(move.dest())->isWhite())
		return 255;
	else
		return 1; // capturing move

	// TODO: 4 for en passant pawn capture.
}

uint8_t Board::gameOver()
{

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
	board_[0][4] = whiteKing = make_shared<King>(true);
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
	board_[7][4] = blackKing = make_shared<King>(false);
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

				if (board_[i][j]->isWhite())
					whitePieces_.push_back(board_[i][j]);
				else
					blackPieces_.push_back(board_[i][j]);
			}
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
	os << "\n    A   B   C   D   E   F   G   H\n";
	os << "  +---+---+---+---+---+---+---+---+\n";

	for (uint8_t i = 0; i < 8; i++)
	{
		int currIndex = b.playingAsWhite_ ? (8 - i) : (i + 1);
		os << currIndex << " ";
		for (uint8_t j = 0; j < 8; j++)
		{
			os << "| " << b.getArtAt( Pos2D(b.playingAsWhite_ ? (7 - i) : i, j) ) << " ";
		}
		os << "| " << currIndex << '\n';
		os << "  +---+---+---+---+---+---+---+---+\n";
	}
	os << "    A   B   C   D   E   F   G   H\n";

	return os;
}