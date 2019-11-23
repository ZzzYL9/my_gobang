#include "chessboard.h"

void ChessBoard::init()
{
	for (int i = 0; i < LEN+2; i++)
	{
		for (int j = 0; j < LEN+2; j++)
		{
			p[i][j] = 0;
		}
	}
}

void ChessBoard::drawboard(int i, int j)
{
	if (p[i][j] == 1)
		cout << "¡ð";
	else if (p[i][j] == 2)
		cout << "¡ñ";
	else if (p[i][j] == -1)
		cout << "¡÷";
	else if (p[i][j] == -2)
		cout << "¡ø";
	else if (i == LEN)
	{
		if (j == 1) {
			cout << "©³";
			return;
		}
		if (j == LEN) {
			cout << "©·";
			return;
		}
		cout << "©Ó";
		return;
	}
	else if (i == 1)
	{
		if (j == 1) {
			cout << "©»";
			return;
		}
		if (j == LEN) {
			cout << "©¿";
			return;
		}
		cout << "©Û";
		return;
	}
	else if (j == 1) {
		cout << "©Ä";
		return;
	}
	else if (j == LEN) {
		cout << "©Ì";
		return;
	}
	else
		cout << "©à";
}

void ChessBoard::show()
{
	int row = 0, col = 0;
	char col_name = 'A';
	cout << endl << endl << endl;

	for (row = LEN; row >= 1; row--)
	{
		cout << endl << "  " << resetiosflags(ios::right) << setw(2) << row;
		for (col = 1; col <= LEN; col++)
		{
			drawboard(row, col);
		}
	}
	col_name = 'A';
	cout << endl << "     ";

	for (col = 1; col <= LEN; col++) {
		cout << col_name << " ";
		col_name++;
	}
	cout << endl << endl;
}