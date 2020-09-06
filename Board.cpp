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
	// tell the piece where it will be
	pieceHere->setPos(move.dest());
	pieceHere->setHasMoved(true);

	if (pieceHere->canPromote())
	{
		pieceHere = make_shared<Queen>(pieceHere->isWhite());
	}

	// reference there
	setPiece(move.dest(), pieceHere);
	// remove piece from here
	setPiece(move.src(), nullptr);	
}

bool Board::isValidMove(const Move& move)
{
	if (move.intention() == 255)
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

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

uint8_t Board::findIntention(const Move& move)
{
	Pos2D moveDelta = move.dest() - move.src();
	// can't move empty squares
	if (pieceAt(move.src()) == nullptr)
		return 255;

	// bishop-like movement
	if (moveDelta.x == moveDelta.y)
	{
		// TODO: make a method or something to make this thing readable
		// (its a for loop that goes the direction of the delta)
		for (int i = sgn(moveDelta.x); i < abs(moveDelta.x); i += sgn(moveDelta.x))
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
		for (int i = sgn(moveDelta.y); i < abs(moveDelta.y); i += sgn(moveDelta.y))
		{
			if (board_[move.src().x][move.src().y + i] != nullptr)
			{
				return 253; // trying to jump over a piece with a rook (y axis)
			}
		}
	}
	else if (moveDelta.y == 0) // double square initial pawn move is also prevented from jumping pieces here
	{
		for (int i = sgn(moveDelta.x); i < abs(moveDelta.x); i += sgn(moveDelta.x))
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
	if (pieceAt(move.src())->isWhite() == pieceAt(move.dest())->isWhite())
		return 255;
	else
		return 1; // capturing move

	// TODO: return 2 for castling, 3 for en passant pawn capture.
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
	board_[0][4] = make_shared<King>(true);
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
	board_[7][4] = make_shared<King>(false);
	board_[7][5] = make_shared<Bishop>(false);
	board_[7][6] = make_shared<Knight>(false);
	board_[7][7] = make_shared<Rook>(false);

	// tell each piece what square they're on
	for (int8_t i = 0; i < 8; i++)
	{
		for (int8_t j = 0; j < 8; j++)
		{
			if (board_[i][j] != nullptr)
				board_[i][j]->setPos({ i, j });
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
	os << "  +---+---+---+---+---+---+---+---+\n";

	for (uint8_t i = 0; i < 8; i++)
	{
		os << (b.playingAsWhite_ ? (8 - i) : (i + 1)) << " ";
		for (uint8_t j = 0; j < 8; j++)
		{
			os << "| " << b.getArtAt( Pos2D(b.playingAsWhite_ ? (7 - i) : i, j) ) << " ";
		}
		os << "|\n";
		os << "  +---+---+---+---+---+---+---+---+\n";
	}
	os << "    A   B   C   D   E   F   G   H\n";

	return os;
}