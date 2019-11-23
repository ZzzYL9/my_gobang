#pragma once
#include "chessboard.h"


class Player
{
private:
	int CG_x;//玩家坐标
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
	bool IsEmpty(Player *player);//判断该位置是否可以落子
	int PTPgame(Player *player, int p1_2);//人人对战
	bool Player_victory(Player *player);//判断玩家是否胜利

	void PTCgame();//人机对战
	bool Computer(Player *player, int choice);
};

