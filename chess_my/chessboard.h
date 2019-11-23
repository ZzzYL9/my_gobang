#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

#define LEN 15
class ChessBoard//ÆåÅÌÀà
{
public:
	void init();
	void drawboard(int i, int j);
	void show();

	int p[LEN + 2][LEN + 2]; //0¿Õ1°×2ºÚ  1¡ğ2¡ñ -1¡÷-2¡ø
};