#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

#define LEN 15
class ChessBoard//������
{
public:
	void init();
	void drawboard(int i, int j);
	void show();

	int p[LEN + 2][LEN + 2]; //0��1��2��  1��2�� -1��-2��
};