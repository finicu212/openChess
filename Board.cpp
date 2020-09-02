#include "Board.h"

extern bool g_playingAsWhite;

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
	if (pHere == nullptr)
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
	// reference there
	setPiece(move.dest(), pieceHere);
	// tell the piece where it will be
	pieceAt(move.src())->setPos(move.dest());
	// remove piece from here
	setPiece(move.src(), shared_ptr<Piece>(nullptr));	
}

Board::Board()
{
	// initialize the board with nullptrs
	board.resize(8);
	for (uint8_t i = 0; i < 8; i++)
	{
		board[i].resize(8, shared_ptr<Piece>(nullptr));
	}

	// black major pieces
	board[0][0] = shared_ptr<Piece>(new Rook(false));
	board[0][1] = shared_ptr<Piece>(new Knight(false));
	board[0][2] = shared_ptr<Piece>(new Bishop(false));
	board[0][3] = shared_ptr<Piece>(new King(false));
	board[0][4] = shared_ptr<Piece>(new Queen(false));
	board[0][5] = shared_ptr<Piece>(new Bishop(false));
	board[0][6] = shared_ptr<Piece>(new Knight(false));
	board[0][7] = shared_ptr<Piece>(new Rook(false));

	// black pawns
	for (uint8_t i = 0; i < 8; i++)
	{
		board[1][i] = shared_ptr<Piece>(new Pawn(false));
	}

	// white pawns
	for (uint8_t i = 0; i < 8; i++)
	{
		board[6][i] = shared_ptr<Piece>(new Pawn(true));
	}

	// white major pieces
	board[7][0] = shared_ptr<Piece>(new Rook(true));
	board[7][1] = shared_ptr<Piece>(new Knight(true));
	board[7][2] = shared_ptr<Piece>(new Bishop(true));
	board[7][3] = shared_ptr<Piece>(new King(true));
	board[7][4] = shared_ptr<Piece>(new Queen(true));
	board[7][5] = shared_ptr<Piece>(new Bishop(true));
	board[7][6] = shared_ptr<Piece>(new Knight(true));
	board[7][7] = shared_ptr<Piece>(new Rook(true));

	// tell each piece what square they're on
	for (uint8_t i = 0; i < 8; i++)
	{
		for (uint8_t j = 0; j < 8; j++)
		{
			if (board[i][j] != nullptr)
				board[i][j]->setPos({ i, j });
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Board& b)
{
	os << "  +---+---+---+---+---+---+---+---+\n";

	for (uint8_t i = 0; i < 8; i++)
	{
		os << (g_playingAsWhite ? (8 - i) : (i + 1)) << " ";
		for (uint8_t j = 0; j < 8; j++)
		{
			os << "| " << b.getArtAt({ i, j }) << " ";
		}
		os << "|\n";
		os << "  +---+---+---+---+---+---+---+---+\n";
	}
	os << "    A   B   C   D   E   F   G   H\n";

	return os;
}