#include <iostream>
#include "chessboard.h"
#include "chessgame.h"

int main()
{
	ChessGame *game = new ChessGame;
	game->start();

	system("pause");
	return 0;
}