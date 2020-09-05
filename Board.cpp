#include "Board.h"

shared_ptr<Piece> Board::pieceAt(const Pos2D& pos) const
{
	return board[pos.x][pos.y];
}

void Board::setPiece(const Pos2D& pos, const shared_ptr<Piece>& piece)
{
	board[pos.x][pos.y] = piece;
}

char Board::getArtAt(const Pos2D& pos) const
{
	shared_ptr<Piece> pHere = pieceAt(pos);

	// no piece here
	if (pHere == shared_ptr<Piece>(nullptr))
	{
		// if i + j is even, then it's a shaded square
		bool isShadedSquare = (pos.x + pos.y) % 2 == 0;

		// print . if it's shaded
		return isShadedSquare ? '.' : ' ';
	}

	return pHere->getArt();
}

void Board::movePiece(const Move& move)
{
	shared_ptr<Piece> pieceHere = pieceAt(move.src());
	// tell the piece where it will be
	pieceHere->setPos(move.dest());
	pieceHere->setHasMoved(true);

	if (pieceHere->canPromote())
	{
		pieceHere = make_shared<Queen>(pieceHere->getColor());
	}

	// reference there
	setPiece(move.dest(), pieceHere);
	// remove piece from here
	setPiece(move.src(), shared_ptr<Piece>(nullptr));	
}

bool Board::isValidMove(const Move& move)
{
	if (move.intention() == 255)
		return false;
	
	return pieceAt(move.src())->isValidMove(move);
}

void Board::setPlayingPerspective(bool asWhite)
{
	playingAsWhite = asWhite;
}

bool Board::getPerspective()
{
	return playingAsWhite;
}

uint8_t Board::getIntention(const Move& move)
{
	// can't move empty squares
	if (pieceAt(move.src()) == shared_ptr<Piece>(nullptr))
		return 255;

	if (pieceAt(move.dest()) == shared_ptr<Piece>(nullptr))
		return 0; // standard move

	// can't move on friendly pieces
	if (pieceAt(move.src())->getColor() == pieceAt(move.dest())->getColor())
		return 255;
	else
		return 1; // capturing move

	// TODO: return 2 for castling, 3 for en passant pawn capture.
}

Board::Board()
{
	// initialize the board with nullptrs
	board.resize(8);
	for (uint8_t i = 0; i < 8; i++)
	{
		board[i].resize(8, shared_ptr<Piece>(nullptr));
	}

	// white major pieces
	board[0][0] = make_shared<Rook>(true);
	board[0][1] = make_shared<Knight>(true);
	board[0][2] = make_shared<Bishop>(true);
	board[0][3] = make_shared<Queen>(true);
	board[0][4] = make_shared<King>(true);
	board[0][5] = make_shared<Bishop>(true);
	board[0][6] = make_shared<Knight>(true);
	board[0][7] = make_shared<Rook>(true);

	// white pawns
	for (uint8_t i = 0; i < 8; i++)
	{
		board[1][i] = make_shared<Pawn>(true);
	}

	// black pawns
	for (uint8_t i = 0; i < 8; i++)
	{
		board[6][i] = make_shared<Pawn>(false);
	}

	// black major pieces
	board[7][0] = make_shared<Rook>(false);
	board[7][1] = make_shared<Knight>(false);
	board[7][2] = make_shared<Bishop>(false);
	board[7][3] = make_shared<Queen>(false);
	board[7][4] = make_shared<King>(false);
	board[7][5] = make_shared<Bishop>(false);
	board[7][6] = make_shared<Knight>(false);
	board[7][7] = make_shared<Rook>(false);

	// tell each piece what square they're on
	for (int8_t i = 0; i < 8; i++)
	{
		for (int8_t j = 0; j < 8; j++)
		{
			if (board[i][j] != shared_ptr<Piece>(nullptr))
				board[i][j]->setPos({ i, j });
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
	os << "  +---+---+---+---+---+---+---+---+\n";

	for (uint8_t i = 0; i < 8; i++)
	{
		os << (b.playingAsWhite ? (8 - i) : (i + 1)) << " ";
		for (uint8_t j = 0; j < 8; j++)
		{
			os << "| " << b.getArtAt( Pos2D(b.playingAsWhite ? (7 - i) : i, j) ) << " ";
		}
		os << "|\n";
		os << "  +---+---+---+---+---+---+---+---+\n";
	}
	os << "    A   B   C   D   E   F   G   H\n";

	return os;
}