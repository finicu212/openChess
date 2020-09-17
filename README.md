# openChess

An open-source implementation of the classic game of chess. Clean OOP together with modern C++ (smart pointers, vectors, string_view...) were core concepts ever since this project's inception.

---

![Board picture](https://i.imgur.com/sMmHHXc.png)

## How to play

After compiling, pick a color, by inputting `w` or `b`, this will affect the perspective of the board.

The game will now enter a loop, until one of the game end conditions (stalemate, checkmate..).

To make a move, input a source square, followed by a space, and a destination square. (example: `e2 e4` to move the piece at `e2` to the `e4` square).

**Castling:** To castle, move the king two squares towards the rook with which you want to castle with. Note: standard castling rules apply (see [#32](https://github.com/finicu212/openChess/issues/32) for a succinct overview of the rules, or read the wiki: https://en.wikipedia.org/wiki/Castling)

## Contributing

**Please** give the [gitflow workflow](https://www.atlassian.com/git/tutorials/comparing-workflows#gitflow-workflow) a read. Feel free to pick any issue and start working on it, but make sure to leave a comment first so that multiple people don't work on the same thing at the same time.

Feel free to leave any ideas, bug reports as a new issue.

## Colors

Thanks to [AmiditeX](https://github.com/AmiditeX) for implementing ANSI character sequences. See [#27](https://github.com/finicu212/openChess/issues/27)
