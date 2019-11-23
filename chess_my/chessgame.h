#pragma once
#include "chessboard.h"


class Player
{
private:
	int CG_x;//�������
	int CG_y;

public:
	int get_x() { return CG_x; }
	int get_y() { return CG_y; }

	void set_x(int x) { CG_x = x; }
	void set_y(int y) { CG_y = y; }
};

class ChessGame 
{
private:
	ChessBoard* m_ptBoard = new ChessBoard;

public:
	//void init();
	void start();
	bool IsEmpty(Player *player);//�жϸ�λ���Ƿ��������
	int PTPgame(Player *player, int p1_2);//���˶�ս
	bool Player_victory(Player *player);//�ж�����Ƿ�ʤ��

	void PTCgame();//�˻���ս
	bool Computer(Player *player, int choice);
};

