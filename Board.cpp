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
		pieceHere = shared_ptr<Piece>(new Queen(pieceHere->getColor()));
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
	board[0][0] = shared_ptr<Piece>(new Rook(true));
	board[0][1] = shared_ptr<Piece>(new Knight(true));
	board[0][2] = shared_ptr<Piece>(new Bishop(true));
	board[0][3] = shared_ptr<Piece>(new Queen(true));
	board[0][4] = shared_ptr<Piece>(new King(true));
	board[0][5] = shared_ptr<Piece>(new Bishop(true));
	board[0][6] = shared_ptr<Piece>(new Knight(true));
	board[0][7] = shared_ptr<Piece>(new Rook(true));

	// white pawns
	for (uint8_t i = 0; i < 8; i++)
	{
		board[1][i] = shared_ptr<Piece>(new Pawn(true));
	}

	// black pawns
	for (uint8_t i = 0; i < 8; i++)
	{
		board[6][i] = shared_ptr<Piece>(new Pawn(false));
	}

	// black major pieces
	board[7][0] = shared_ptr<Piece>(new Rook(false));
	board[7][1] = shared_ptr<Piece>(new Knight(false));
	board[7][2] = shared_ptr<Piece>(new Bishop(false));
	board[7][3] = shared_ptr<Piece>(new Queen(false));
	board[7][4] = shared_ptr<Piece>(new King(false));
	board[7][5] = shared_ptr<Piece>(new Bishop(false));
	board[7][6] = shared_ptr<Piece>(new Knight(false));
	board[7][7] = shared_ptr<Piece>(new Rook(false));

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