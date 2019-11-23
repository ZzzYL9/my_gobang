#include "chessgame.h"
#include <conio.h>
#include <windows.h>

int new_x = 0, new_y = 0;
int victory = 0;//保存胜利次数

int four_0_x[11] = { 0 };
int four_0_y[11] = { 0 };

int three_0_x[5] = { 0 };
int three_0_y[5] = { 0 };

void ChessGame::start()
{
	m_ptBoard->init();
	int choice;
	cout << "----------游戏模式----------" << endl;
	cout << "1.人人对战" << endl << "2.人机对战" << endl;
	cout << "请选择游戏模式：";
	cin >> choice;
	if (choice == 1) {
		system("cls");
		m_ptBoard->show();
		Player *p1 = new Player;
		Player *p2 = new Player;
		while (1) {
			if (PTPgame(p1, 1) != 3)
				break;
			m_ptBoard->p[new_x][new_y] = 1;
			if (Player_victory(p1))
				break;

			if (PTPgame(p2, 2) != 3)
				break;
			m_ptBoard->p[new_x][new_y] = 2;
			if (Player_victory(p2))
				break;
		}

	}
	else if (choice == 2) {
		system("cls");
		PTCgame();
	}
	else
		return start();
}

int ChessGame::PTPgame(Player *player, int p1_2)//p1_2为2时，player执白棋，为1时，player执黑棋
{
	int x, y;
	char c[10] = { 0 };
	while (1) {
		cout << "请玩家" << p1_2 << "输入坐标：（例如：H8）";

		time_t Time = time(0);
		Time += 15;//秒数, 你可以自己改

		while (Time > time(0))
		{
			if (_kbhit())    //kbhit, 检测是否有字符输入(输入缓冲区是否为空), 它只检测, 不吸收字符
			{
				cin >> c;
				break;
			}
		}

		if (Time <= time(0)) {
			if (p1_2 == 2) {
				cout << endl << "白棋超时，判负！" << endl;
				return 2;//
			}
			else {
				cout << endl << "黑棋超时，判负！" << endl;
				return 1;
			}
		}
		else {
			if (strlen(c) > 3 || strlen(c) < 2)
				goto error;
			if (strlen(c) == 2)
				x = c[1] - '0';
			if (strlen(c) == 3) {
				x = (c[1] - '0') * 10 + (c[2] - '0');
			}
			if (c[0] >= 'A' && c[0] <= 'Z' && (x >= 0 && x <= 15)) {
				y = c[0] - 64;
				player->set_x(x);
				player->set_y(y);
				if (IsEmpty(player)) {        //判断坐标是否合法
					new_x = x;
					new_y = y;
					break;
				}
			}
			
			error:cout << "坐标不合法，请重新输入：" << endl;
		}


	}
	if (p1_2 == 1) {
		m_ptBoard->p[x][y] = -1;
	}
	else {
		m_ptBoard->p[x][y] = -2;
	}
	system("cls");
	m_ptBoard->show();
	return 3;
}

bool ChessGame::IsEmpty(Player *player)
{
	if (m_ptBoard->p[player->get_x()][player->get_y()] != 0)
		return false;
	else
		return true;
}

void ChessGame::PTCgame()
{
	int choice;
	int score_player = 0;//保存玩家分数
	int score_com = 0;//保存电脑分数
					  //int play;//保存玩家是电脑还是人
	cout << "1.电脑先手" << endl << "2.玩家先手" << endl;
	cout << "请选择：";
	cin >> choice;
	//更换为玩家执白棋！！！！！！！！！！！？？？？？？？？？
	if (choice == 1) {
		system("cls");
		cout << "*************第一局*************" << endl;
		m_ptBoard->p[8][8] = -1;

		m_ptBoard->show();
		m_ptBoard->p[8][8] = 1;
		Player *player = new Player;
		Player *AI = new Player;
		while (1) {
			int flag = PTPgame(player, 2);
			if (flag == 1) {//电脑执黑棋，玩家执白棋
				score_player += 2;
				cout << "第一局玩家胜利，记2分！(稍等5秒进入下一局)" << endl;
				Sleep(5000);
				break;
			}
			if (flag == 2) {
				score_com += 2;
				cout << "第一局电脑胜利，记2分！(稍等5秒进入下一局)" << endl;
				Sleep(5000);
				break;
			}

			m_ptBoard->p[new_x][new_y] = 2;
			if (Player_victory(player)) {
				score_player += 2;
				cout << "第一局玩家胜利，记2分！(稍等5秒进入下一局)" << endl;
				Sleep(5000);
				break;
			}

			if (Computer(AI, choice)) {
				score_com += 2;
				cout << "第一局电脑胜利，记2分！(稍等5秒进入下一局)" << endl;
				Sleep(5000);
				break;
			}
			m_ptBoard->p[new_x][new_y] = 1;


		}
		system("cls");
		cout << "***************第二局***************" << endl;
		m_ptBoard->init();
		four_0_x[11] = { 0 };
		four_0_y[11] = { 0 };

		three_0_x[5] = { 0 };
		three_0_y[5] = { 0 };

		m_ptBoard->show();
		while (1) {
			int flag = PTPgame(player, choice);
			if (flag == 1) {//电脑执白棋，玩家执黑棋
				score_com += 2;
				cout << "游戏结束！玩家得分：" << score_player << "   电脑得分：" << score_com << endl;
				break;
			}
			if (flag == 2) {//电脑执白棋，玩家执黑棋
				score_player += 2;
				cout << "游戏结束！玩家得分：" << score_player << "   电脑得分：" << score_com << endl;
				break;
			}
			m_ptBoard->p[new_x][new_y] = 1;
			if (Player_victory(player)) {
				score_player += 2;
				cout << "游戏结束！玩家得分：" << score_player << "   电脑得分：" << score_com << endl;
				break;
			}

			if (Computer(AI, 2)) {//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!未完成
				score_com += 2;
				cout << "游戏结束！玩家得分：" << score_player << "   电脑得分：" << score_com << endl;
				break;
			}
			m_ptBoard->p[new_x][new_y] = 2;
		}
	}
	else if (choice == 2) {
		system("cls");
		cout << "*************第一局*************" << endl;
		m_ptBoard->show();
		Player *player = new Player;
		Player *AI = new Player;
		while (1) {
			int flag = PTPgame(player, 1);
			if (flag == 1) {//电脑执白棋，玩家执黑棋
				score_com += 2;
				cout << "第一局电脑胜利，记2分！(稍等5秒进入下一局)" << endl;
				Sleep(5000);
				break;
			}
			if (flag == 2) {//电脑执白棋，玩家执黑棋
				score_player += 2;
				cout << "第一局玩家胜利，记2分！(稍等5秒进入下一局)" << endl;
				Sleep(5000);
				break;
			}
			m_ptBoard->p[new_x][new_y] = 1;
			if (Player_victory(player)) {
				score_player += 2;
				cout << "第一局玩家胜利，记2分！(稍等5秒进入下一局)" << endl;
				Sleep(5000);
				break;
			}

			if (Computer(AI, choice)) {
				score_com += 2;
				cout << "第一局电脑胜利，记2分！(稍等5秒进入下一局)" << endl;
				Sleep(5000);
				break;
			}
			m_ptBoard->p[new_x][new_y] = 2;
		}
		system("cls");
		cout << "***************第二局***************" << endl;
		m_ptBoard->init();
		four_0_x[11] = { 0 };
		four_0_y[11] = { 0 };

		three_0_x[5] = { 0 };
		three_0_y[5] = { 0 };
		m_ptBoard->p[8][8] = -1;
		m_ptBoard->show();
		m_ptBoard->p[8][8] = 1;
		m_ptBoard->show();
		while (1) {
			int flag = PTPgame(player, choice);
			if (flag == 1) {//电脑执黑棋，玩家执白棋
				score_player += 2;
				cout << "游戏结束！玩家得分：" << score_player << "   电脑得分：" << score_com << endl;
				break;
			}
			if (flag == 2) {//电脑执黑棋，玩家执白棋
				score_com += 2;
				cout << "游戏结束！玩家得分：" << score_player << "   电脑得分：" << score_com << endl;
				break;
			}
			m_ptBoard->p[new_x][new_y] = 2;
			if (Player_victory(player)) {
				score_player += 2;
				cout << "游戏结束！玩家得分：" << score_player << "   电脑得分：" << score_com << endl;
				break;
			}

			if (Computer(AI, 1)) {
				score_com += 2;
				cout << "游戏结束！玩家得分：" << score_player << "   电脑得分：" << score_com << endl;
				break;
			}
			m_ptBoard->p[new_x][new_y] = 1;
		}

	}
	else {
		cout << "输入错误，请重新选择！";
		return PTCgame();
	}

}

//？？？？？？？？？？？？
bool ChessGame::Computer(Player *player, int choice)
{
	int kill_chess_color;//要围堵的棋的颜色
	int put_chess_color;//要下的棋的颜色
	int chess; //落子颜色
	if (choice == 1) {
		kill_chess_color = 1;//白色
		put_chess_color = 2;
		chess = -1;//如果是电脑先手，则要下黑棋
	}
	else {
		kill_chess_color = 2;//黑色
		put_chess_color = 1;
		chess = -2;//如果是玩家先手，则电脑要下白棋
	}

	int score[LEN + 2][LEN + 2] = { 0 };
	for (int i = 1; i <= LEN; i++)
	{
		for (int j = 1; j < LEN; j++)
		{
			if ((m_ptBoard->p[i][j] == 0))
			{
				if (((i - 3)>-1))				//纵向
				{
					//堵黑棋
					if ((m_ptBoard->p[i - 3][j] == kill_chess_color) && (m_ptBoard->p[i - 2][j] == kill_chess_color) && (m_ptBoard->p[i - 1][j] == kill_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i - 2][j] == kill_chess_color) && (m_ptBoard->p[i - 1][j] == kill_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i - 1][j] == kill_chess_color)
					{
						score[i][j] += 1;
					}
					//下白棋
					if ((m_ptBoard->p[i - 3][j] == put_chess_color) && (m_ptBoard->p[i - 2][j] == put_chess_color) && (m_ptBoard->p[i - 1][j] == put_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i - 2][j] == put_chess_color) && (m_ptBoard->p[i - 1][j] == put_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i - 1][j] == put_chess_color)
					{
						score[i][j] += 10;
					}

				}
				if ((i + 3) <= LEN)
				{
					//堵黑棋
					if ((m_ptBoard->p[i + 3][j] == kill_chess_color) && (m_ptBoard->p[i + 2][j] == kill_chess_color) && (m_ptBoard->p[i + 1][j] == kill_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i + 2][j] == kill_chess_color) && (m_ptBoard->p[i + 1][j] == kill_chess_color))
					{
						score[i][j] += 50;
					}
					if ((m_ptBoard->p[i + 1][j] == kill_chess_color))
					{
						score[i][j] += 1;
					}
					//下白棋
					if ((m_ptBoard->p[i + 3][j] == put_chess_color) && (m_ptBoard->p[i + 2][j] == put_chess_color) && (m_ptBoard->p[i + 1][j] == put_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i + 2][j] == put_chess_color) && (m_ptBoard->p[i + 1][j] == put_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i + 1][j] == put_chess_color)
					{
						score[i][j] += 10;
					}
				}
				//----------------------------------------------------------------
				if ((j - 3)>-1)			//横向
				{
					//堵黑棋
					if ((m_ptBoard->p[i][j - 3] == kill_chess_color) && (m_ptBoard->p[i][j - 2] == kill_chess_color) && (m_ptBoard->p[i][j - 1] == kill_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i][j - 2] == kill_chess_color) && (m_ptBoard->p[i][j - 1] == kill_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i][j - 1] == kill_chess_color)
					{
						score[i][j] += 1;
					}
					//下白棋
					if ((m_ptBoard->p[i][j - 3] == put_chess_color) && (m_ptBoard->p[i][j - 2] == put_chess_color) && (m_ptBoard->p[i][j - 1] == put_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i][j - 2] == put_chess_color) && (m_ptBoard->p[i][j - 1] == put_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i][j - 1] == put_chess_color)
					{
						score[i][j] += 10;
					}
				}
				if ((j + 3) <= LEN)
				{
					if ((m_ptBoard->p[i][j + 3] == kill_chess_color) && (m_ptBoard->p[i][j + 2] == kill_chess_color) && (m_ptBoard->p[i][j + 1] == kill_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i][j + 2] == kill_chess_color) && (m_ptBoard->p[i][j + 1] == kill_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i][j + 1] == kill_chess_color)
					{
						score[i][j] += 1;
					}

					if ((m_ptBoard->p[i][j + 3] == put_chess_color) && (m_ptBoard->p[i][j + 2] == put_chess_color) && (m_ptBoard->p[i][j + 1] == put_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i][j + 2] == put_chess_color) && (m_ptBoard->p[i][j + 1] == put_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i][j + 1] == put_chess_color)
					{
						score[i][j] += 10;
					}
				}
				//================================================================
				if (((j - 3)>-1) && ((i - 3)>-1))		// 斜向 \向
				{
					//堵黑棋
					if ((m_ptBoard->p[i - 3][j - 3] == kill_chess_color) && (m_ptBoard->p[i - 2][j - 2] == kill_chess_color) && (m_ptBoard->p[i - 1][j - 1] == kill_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i - 2][j - 2] == kill_chess_color) && (m_ptBoard->p[i - 1][j - 1] == kill_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i - 1][j - 1] == kill_chess_color)
					{
						score[i][j] += 1;
					}
					//下白棋
					if ((m_ptBoard->p[i - 3][j - 3] == put_chess_color) && (m_ptBoard->p[i - 2][j - 2] == put_chess_color) && (m_ptBoard->p[i - 1][j - 1] == put_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i - 2][j - 2] == put_chess_color) && (m_ptBoard->p[i - 1][j - 1] == put_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i - 1][j - 1] == put_chess_color)
					{
						score[i][j] += 10;
					}

				}
				if (((j + 3) <= LEN) && ((i + 3) <= LEN))
				{
					if ((m_ptBoard->p[i + 3][j + 3] == kill_chess_color) && (m_ptBoard->p[i + 2][j + 2] == kill_chess_color) && (m_ptBoard->p[i + 1][j + 1] == kill_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i + 2][j + 2] == kill_chess_color) && (m_ptBoard->p[i + 1][j + 1] == kill_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i + 1][j + 1] == kill_chess_color)
					{
						score[i][j] += 1;
					}

					if ((m_ptBoard->p[i + 3][j + 3] == put_chess_color) && (m_ptBoard->p[i + 2][j + 2] == put_chess_color) && (m_ptBoard->p[i + 1][j + 1] == put_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i + 2][j + 2] == put_chess_color) && (m_ptBoard->p[i + 1][j + 1] == put_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i + 1][j + 1] == put_chess_color)
					{
						score[i][j] += 10;
					}
				}

				if (((i - 3)>-1) && ((j + 3) <= LEN))		//  /向
				{
					//堵黑棋
					if ((m_ptBoard->p[i - 3][j + 3] == kill_chess_color) && (m_ptBoard->p[i - 2][j + 2] == kill_chess_color) && (m_ptBoard->p[i - 1][j + 1] == kill_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i - 2][j + 2] == kill_chess_color) && (m_ptBoard->p[i - 1][j + 1] == kill_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i - 1][j + 1] == kill_chess_color)
					{
						score[i][j] += 1;
					}
					//下白棋
					if ((m_ptBoard->p[i - 3][j + 3] == put_chess_color) && (m_ptBoard->p[i - 2][j + 2] == put_chess_color) && (m_ptBoard->p[i - 1][j + 1] == put_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i - 2][j + 2] == put_chess_color) && (m_ptBoard->p[i - 1][j + 1] == put_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i - 1][j + 1] == put_chess_color)
					{
						score[i][j] += 10;
					}
				}
				if (((i + 3) <= LEN) && ((j - 3)>-1))//？？？？？？？？？？？？？？？？？
				{
					if ((m_ptBoard->p[i + 3][j - 3] == kill_chess_color) && (m_ptBoard->p[i + 2][j - 2] == kill_chess_color) && (m_ptBoard->p[i + 1][j - 1] == kill_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i + 2][j - 2] == kill_chess_color) && (m_ptBoard->p[i + 1][j - 1] == kill_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i + 1][j - 1] == kill_chess_color)
					{
						score[i][j] += 1;
					}

					if ((m_ptBoard->p[i + 3][j - 3] == put_chess_color) && (m_ptBoard->p[i + 2][j - 2] == put_chess_color) && (m_ptBoard->p[i + 1][j - 1] == put_chess_color))
					{
						score[i][j] += 1000;
					}
					if ((m_ptBoard->p[i + 2][j - 2] == put_chess_color) && (m_ptBoard->p[i + 1][j - 1] == put_chess_color))
					{
						score[i][j] += 50;
					}
					if (m_ptBoard->p[i + 1][j - 1] == put_chess_color)
					{
						score[i][j] += 10;
					}
				}
			}
		}
	}

	int x = 0, y = 0;
	do
	{
		x = rand() % LEN;
		y = rand() % LEN;
	} while (m_ptBoard->p[x][y] == 0);

	int max = score[0][0];
	for (int i = 1; i <= LEN; i++)
	{
		for (int j = 1; j <= LEN; j++)
		{
			if (score[i][j]>max)
			{
				max = score[i][j];
				new_x = i, new_y = j;
			}
		}
	}
	player->set_x(new_x);
	player->set_y(new_y);
	m_ptBoard->p[new_x][new_y] = chess;
	system("cls");
	m_ptBoard->show();
	if (Player_victory(player)) {
		return true;
		victory++;
	}

}

int three_forbid = 0;//统计形成活三的个数
int four_forbid = 0;//统计形成四的个数

					//判断是否胜利的算法
bool ChessGame::Player_victory(Player *player)
{
	int white_num = 0;//统计白棋和黑棋数量
	int black_num = 0;

	//横向判断
	for (int i = 0; i < LEN; i++)
	{
		if (m_ptBoard->p[player->get_x()][i] == 0)
		{
			black_num = 0;
			white_num = 0;
		}
		if ((m_ptBoard->p[player->get_x()][i] == 1) || (m_ptBoard->p[player->get_x()][i] == -1))
		{
			black_num++;

			//四四禁手
			if (black_num == 1) {
				if (m_ptBoard->p[player->get_x()][i - 1] == 0 && m_ptBoard->p[player->get_x()][i + 1] == 0 && m_ptBoard->p[player->get_x()][i + 2] == 1 &&
					m_ptBoard->p[player->get_x()][i + 3] == 1 && m_ptBoard->p[player->get_x()][i + 4] == 1 && m_ptBoard->p[player->get_x()][i + 5] == 0) {
					for (int i = 0; i < 3; i++)
						four_0_x[i] = player->get_x();
					four_0_y[0] = i - 1; four_0_y[1] = i + 1; four_0_y[2] = i + 5;
					four_forbid++;
					three_forbid--;//活三变为四，则活三数量减一
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}//三三禁手
				else if (m_ptBoard->p[player->get_x()][i - 1] == 0 && ((m_ptBoard->p[player->get_x()][i + 1] == 0 && m_ptBoard->p[player->get_x()][i + 2] == 1 && m_ptBoard->p[player->get_x()][i + 3] == 1 && m_ptBoard->p[player->get_x()][i + 4] == 0)
					|| (m_ptBoard->p[player->get_x()][i + 1] == 1 && m_ptBoard->p[player->get_x()][i + 2] == 0 && m_ptBoard->p[player->get_x()][i + 3] == 1 && m_ptBoard->p[player->get_x()][i + 4] == 0))) {
					for (int i = 0; i < 3; i++)
						three_0_x[i] = player->get_x();
					three_0_y[0] = i - 1;
					if (m_ptBoard->p[player->get_x()][i + 1] == 0) {
						three_0_y[1] = i + 1; three_0_y[2] = i + 4;
					}
					if (m_ptBoard->p[player->get_x()][i + 1] == 1) {
						three_0_y[1] = i + 2; three_0_y[2] = i + 4;
					}

					three_forbid++;
					if (three_forbid > 1) {
						cout << endl << "黑方三三禁手！白方胜利！" << endl;
						three_forbid = 0;
						return true;
						break;
					}
				}
			}

			if (black_num == 3) {
				//四四禁手
				if (m_ptBoard->p[player->get_x()][i - 3] == 0 && m_ptBoard->p[player->get_x()][i + 1] == 0 &&
					m_ptBoard->p[player->get_x()][i + 2] == 1 && m_ptBoard->p[player->get_x()][i + 3] == 0) {
					//两个i不同！！！！！！！！！！！！
					for (int i = 3; i < 6; i++)
						four_0_x[i] = player->get_x();
					four_0_y[3] = i - 3; four_0_y[4] = i + 1; four_0_y[5] = i + 3;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}//三三禁手
				else if (m_ptBoard->p[player->get_x()][i - 3] == 0 && m_ptBoard->p[player->get_x()][i + 1] == 0) {
					three_0_x[3] = player->get_x();
					three_0_y[3] = i - 3;
					three_0_x[4] = player->get_x();
					three_0_y[4] = i + 1;
					three_forbid++;
					if (three_forbid > 1) {
						cout << endl << "黑方三三禁手！白方胜利！" << endl;
						three_forbid = 0;
						return true;
						break;
					}
				}

			}

			//四四禁手
			if (black_num == 4) {
				if (m_ptBoard->p[player->get_x()][i - 4] == 0 && m_ptBoard->p[player->get_x()][i + 1] == 0) {
					for (int i = 6; i < 8; i++)
						four_0_x[i] = player->get_x();
					four_0_y[6] = i - 4; four_0_y[7] = i + 1;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}
			}
			if (black_num == 2) {
				if (m_ptBoard->p[player->get_x()][i - 2] == 0 && m_ptBoard->p[player->get_x()][i + 1] == 0 &&
					m_ptBoard->p[player->get_x()][i + 2] == 1 && m_ptBoard->p[player->get_x()][i + 3] == 1 &&
					m_ptBoard->p[player->get_x()][i + 4] == 0) {
					for (int i = 8; i < 11; i++)
						four_0_x[i] = player->get_x();
					four_0_y[8] = i - 2; four_0_y[9] = i + 1; four_0_y[10] = i + 4;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}
			}

			white_num = 0;
			if (black_num == 5)
			{
				//判断长连禁手
				if ((m_ptBoard->p[player->get_x()][i + 1] != 1) && (m_ptBoard->p[player->get_x()][i + 1] != -1)) {
					cout << endl << "黑方胜利！" << endl;
					return true;
					break;
				}
				else {
					cout << endl << "黑方长连禁手！白方胜利！" << endl;
					return true;
					break;
				}

			}
		}
		if ((m_ptBoard->p[player->get_x()][i] == 2) || (m_ptBoard->p[player->get_x()][i] == -2))
		{
			white_num++;
			black_num = 0;
			for (int j = 0; j < 11; j++)
				if (player->get_x() == three_0_x[j] && i == three_0_y[j])
					three_forbid--;
			for (int k = 0; k < 5; k++)
				if (player->get_x() == four_0_x[k] && i == four_0_y[k])
					four_forbid--;
			if (white_num == 5)
			{
				cout << endl << "白方胜利！" << endl;
				return true;
				break;
			}
		}
	}

	//纵向判断
	black_num = 0, white_num = 0;
	for (int i = 0; i < LEN; i++)
	{

		if (m_ptBoard->p[i][player->get_y()] == 0)
		{
			black_num = 0;
			white_num = 0;
		}
		if ((m_ptBoard->p[i][player->get_y()] == 1) || (m_ptBoard->p[i][player->get_y()] == -1))
		{
			black_num++;

			//四四禁手
			if (black_num == 1) {
				if (m_ptBoard->p[i - 1][player->get_y()] == 0 && m_ptBoard->p[i + 1][player->get_y()] == 0 && m_ptBoard->p[i + 2][player->get_y()] == 1 &&
					m_ptBoard->p[i + 3][player->get_y()] == 1 && m_ptBoard->p[i + 4][player->get_y()] == 1 && m_ptBoard->p[i + 5][player->get_y()] == 0) {
					//for(int j = 0; j < 3)
					for (int i = 0; i < 3; i++)
						four_0_y[i] = player->get_y();
					four_0_x[0] = i - 1; four_0_x[1] = i + 1; four_0_x[2] = i + 5;

					four_forbid++;
					three_forbid--;//活三变为四，则活三数量减一
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}//三三禁手
				else if (m_ptBoard->p[i - 1][player->get_y()] == 0 && (m_ptBoard->p[i + 1][player->get_y()] == 0 && m_ptBoard->p[i + 2][player->get_y()] == 1 && m_ptBoard->p[i + 3][player->get_y()] == 1 && m_ptBoard->p[i + 4][player->get_y()] == 0)
					|| (m_ptBoard->p[i + 1][player->get_y()] == 1 && m_ptBoard->p[i + 2][player->get_y()] == 0 && m_ptBoard->p[i + 3][player->get_y()] == 1 && m_ptBoard->p[i + 4][player->get_y()] == 0)) {
					for (int i = 0; i < 3; i++)
						three_0_y[i] = player->get_y();
					three_0_x[0] = i - 1;
					if (m_ptBoard->p[i + 1][player->get_y()] == 0) {
						three_0_x[1] = i + 1; three_0_x[2] = i + 4;
					}
					if (m_ptBoard->p[i + 1][player->get_y()] == 1) {
						three_0_x[1] = i + 2; three_0_x[2] = i + 4;
					}
					three_forbid++;
					if (three_forbid > 1) {
						cout << endl << "黑方三三禁手！白方胜利！" << endl;
						three_forbid = 0;
						return true;
						break;
					}
				}
			}

			if (black_num == 3) {
				//四四禁手
				if (m_ptBoard->p[i - 3][player->get_y()] == 0 && m_ptBoard->p[i + 1][player->get_y()] == 0 &&
					m_ptBoard->p[i + 2][player->get_y()] == 1 && m_ptBoard->p[i + 3][player->get_y()] == 0) {
					for (int i = 3; i < 6; i++)
						four_0_y[i] = player->get_y();
					four_0_x[3] = i - 3; four_0_x[4] = i + 1; four_0_x[5] = i + 3;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}//三三禁手
				else if (m_ptBoard->p[i - 3][player->get_y()] == 0 && m_ptBoard->p[i + 1][player->get_y()] == 0) {
					three_0_x[3] = i - 3;
					three_0_y[3] = player->get_y();
					three_0_x[4] = i + 1;
					three_0_y[4] = player->get_y();
					three_forbid++;
					if (three_forbid > 1) {
						cout << endl << "黑方三三禁手！白方胜利！" << endl;
						three_forbid = 0;
						return true;
						break;
					}
				}
			}

			//四四禁手
			if (black_num == 4) {
				if (m_ptBoard->p[i - 4][player->get_y()] == 0 && m_ptBoard->p[i + 1][player->get_y()] == 0) {
					for (int i = 6; i < 8; i++)
						four_0_y[i] = player->get_y();
					four_0_x[6] = i - 4; four_0_x[7] = i + 1;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}
			}
			if (black_num == 2) {
				if (m_ptBoard->p[i - 2][player->get_y()] == 0 && m_ptBoard->p[i + 1][player->get_y()] == 0 &&
					m_ptBoard->p[i + 2][player->get_y()] == 1 && m_ptBoard->p[i + 3][player->get_y()] == 1 &&
					m_ptBoard->p[i + 4][player->get_y()] == 0) {
					for (int i = 8; i < 11; i++)
						four_0_y[i] = player->get_y();
					four_0_x[8] = i - 2; four_0_x[9] = i + 1; four_0_x[10] = i + 4;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}
			}

			white_num = 0;
			if (black_num == 5)
			{
				if ((m_ptBoard->p[i + 1][player->get_y()] == 1) || (m_ptBoard->p[i + 1][player->get_y()] == -1)) {

					cout << endl << "黑方长连禁手！白方胜利！" << endl;
					return true;
					break;
				}
				else {
					cout << endl << "黑方胜利！" << endl;
					return true;
					break;
				}
				//go();
			}
		}
		if ((m_ptBoard->p[i][player->get_y()] == 2) || (m_ptBoard->p[i][player->get_y()] == -2))
		{
			white_num++;
			black_num = 0;
			for (int j = 0; j < 11; j++)
				if (i == three_0_x[j] && player->get_y() == three_0_y[j])
					three_forbid--;
			for (int k = 0; k < 5; k++)
				if (i == four_0_x[k] && player->get_y() == four_0_y[k])
					four_forbid--;
			if (white_num == 5)
			{
				cout << endl << "白方胜利！" << endl;
				return true;
				break;
				//go();
			}
		}
	}

	//斜向(\向)判断
	int x1 = player->get_x(), y1 = player->get_y();
	if (x1>y1)
	{
		x1 = x1 - y1;
		y1 = 0;
	}
	else
	{
		y1 = y1 - x1;
		x1 = 0;
	}
	black_num = 0, white_num = 0;
	while ((x1<LEN) && (y1<LEN))
	{
		if (m_ptBoard->p[x1][y1] == 0)
		{
			black_num = 0;
			white_num = 0;
		}
		if ((m_ptBoard->p[x1][y1] == 1) || (m_ptBoard->p[x1][y1] == -1))
		{
			black_num++;

			//四四禁手
			if (black_num == 1) {
				if (m_ptBoard->p[x1 - 1][y1 - 1] == 0 && m_ptBoard->p[x1 + 1][y1 + 1] == 0 && m_ptBoard->p[x1 + 2][y1 + 2] == 1 &&
					m_ptBoard->p[x1 + 3][y1 + 3] == 1 && m_ptBoard->p[x1 + 4][y1 + 4] == 1 && m_ptBoard->p[x1 + 5][y1 + 5] == 0) {
					four_0_x[0] = x1 - 1; four_0_x[1] = x1 + 1; four_0_x[2] = x1 + 5;
					four_0_y[0] = y1 - 1; four_0_y[1] = y1 + 1; four_0_y[2] = y1 + 5;

					four_forbid++;
					three_forbid--;//活三变为四，则活三数量减一
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}//三三禁手
				else if (m_ptBoard->p[x1 - 1][y1 - 1] == 0 && (m_ptBoard->p[x1 + 1][y1 + 1] == 0 && m_ptBoard->p[x1 + 2][y1 + 2] == 1 && m_ptBoard->p[x1 + 3][y1 + 3] == 1 && m_ptBoard->p[x1 + 4][y1 + 4] == 0)
					|| (m_ptBoard->p[x1 + 1][y1 + 1] == 1 && m_ptBoard->p[x1 + 2][y1 + 2] == 0 && m_ptBoard->p[x1 + 3][y1 + 3] == 1 && m_ptBoard->p[x1 + 4][y1 + 4] == 0)) {
					three_0_x[0] = x1 - 1;
					three_0_y[0] = y1 - 1;
					if (m_ptBoard->p[x1 + 1][y1 + 1] == 0) {
						three_0_x[1] = x1 + 1; three_0_x[2] = x1 + 4;
						three_0_y[1] = y1 + 1; three_0_y[2] = y1 + 4;
					}
					if (m_ptBoard->p[x1 + 1][y1 + 1] == 1) {
						three_0_x[1] = x1 + 2; three_0_x[2] = x1 + 4;
						three_0_y[1] = y1 + 2; three_0_y[2] = y1 + 4;
					}
					three_forbid++;
					if (three_forbid > 1) {
						cout << endl << "黑方三三禁手！白方胜利！" << endl;
						three_forbid = 0;
						return true;
						break;
					}
				}
			}

			if (black_num == 3) {
				//四四禁手(先判断四四禁手，再判断三三禁手)
				if (m_ptBoard->p[x1 - 3][y1 - 3] == 0 && m_ptBoard->p[x1 + 1][y1 + 1] == 0 &&
					m_ptBoard->p[x1 + 2][y1 + 2] == 1 && m_ptBoard->p[x1 + 3][y1 + 3] == 0) {
					four_0_x[3] = x1 - 3; four_0_x[4] = x1 + 1; four_0_x[5] = x1 + 3;
					four_0_y[3] = y1 - 3; four_0_y[4] = y1 + 1; four_0_y[5] = y1 + 3;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}//三三禁手
				else if (m_ptBoard->p[x1 - 3][y1 - 3] == 0 && m_ptBoard->p[x1 + 1][y1 + 1] == 0) {
					three_0_x[3] = x1 - 3; three_0_x[4] = x1 + 1;
					three_0_y[3] = y1 - 3; three_0_y[4] = y1 + 1;
					three_forbid++;
					if (three_forbid > 1) {
						cout << endl << "黑方三三禁手！白方胜利！" << endl;
						three_forbid = 0;
						return true;
						break;
					}
				}

			}

			//四四禁手
			if (black_num == 4) {
				if (m_ptBoard->p[x1 - 4][y1 - 4] == 0 && m_ptBoard->p[x1 + 1][y1 + 1] == 0) {
					four_0_x[6] = x1 - 4; four_0_x[7] = x1 + 1;
					four_0_y[6] = y1 - 4; four_0_y[7] = y1 + 1;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}
			}
			if (black_num == 2) {
				if (m_ptBoard->p[x1 - 2][y1 - 2] == 0 && m_ptBoard->p[x1 + 1][y1 + 1] == 0 &&
					m_ptBoard->p[x1 + 2][y1 + 2] == 1 && m_ptBoard->p[x1 + 3][y1 + 3] == 1 &&
					m_ptBoard->p[x1 + 4][y1 + 4] == 0) {
					four_0_x[8] = x1 - 2; four_0_x[9] = x1 + 1; four_0_x[10] = x1 + 4;
					four_0_y[8] = y1 - 2; four_0_y[9] = y1 + 1; four_0_y[10] = y1 + 4;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}
			}

			white_num = 0;
			if (black_num == 5)
			{
				if ((m_ptBoard->p[x1 + 1][y1 + 1] != 1) && (m_ptBoard->p[x1 + 1][y1 + 1] != -1)) {
					cout << endl << "黑方胜利！" << endl;
					return true;
					break;
				}
				else {
					cout << endl << "黑方长连禁手！白方胜利！" << endl;
					return true;
					break;
				}
				//go();
			}
		}
		if ((m_ptBoard->p[x1][y1] == 2) || (m_ptBoard->p[x1][y1] == -2))
		{
			white_num++;
			black_num = 0;
			for (int j = 0; j < 11; j++)
				if (x1 == three_0_x[j] && y1 == three_0_y[j])
					three_forbid--;
			for (int k = 0; k < 5; k++)
				if (x1 == four_0_x[k] && y1 == four_0_y[k])
					four_forbid--;
			if (white_num == 5)
			{
				cout << endl << "白方胜利！" << endl;
				return true;
				break;
				//go();
			}
		}
		x1++;
		y1++;
	}

	//斜向（/向）判断
	int x2 = player->get_x(), y2 = player->get_y();
	int n = 0;//保存差值

	n = LEN - y2;
	x2 -= n;
	y2 += n;

	black_num = 0, white_num = 0;
	while ((y2 >= 0) && (x2<LEN))
	{
		if (m_ptBoard->p[x2][y2] == 0)
		{
			black_num = 0;
			white_num = 0;
		}
		if ((m_ptBoard->p[x2][y2] == 1) || (m_ptBoard->p[x2][y2] == -1))
		{
			black_num++;

			//四四禁手
			if (black_num == 1) {
				if (m_ptBoard->p[x2 - 1][y2 + 1] == 0 && m_ptBoard->p[x2 + 1][y2 - 1] == 0 && m_ptBoard->p[x2 + 2][y2 - 2] == 1 &&
					m_ptBoard->p[x2 + 3][y2 - 3] == 1 && m_ptBoard->p[x2 + 4][y2 - 4] == 1 && m_ptBoard->p[x2 + 5][y2 - 5] == 0) {
					four_0_x[0] = x2 - 1; four_0_x[1] = x2 + 1; four_0_x[2] = x2 + 5;
					four_0_y[0] = y2 + 1; four_0_y[1] = y2 - 1; four_0_y[2] = y2 - 5;
					four_forbid++;
					three_forbid--;//活三变为四，则活三数量减一
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}//三三禁手
				else if (m_ptBoard->p[x2 - 1][y2 + 1] == 0 && (m_ptBoard->p[x2 + 1][y2 - 1] == 0 && m_ptBoard->p[x2 + 2][y2 - 2] == 1 && m_ptBoard->p[x2 + 3][y2 - 3] == 1 && m_ptBoard->p[x2 + 4][y2 - 4] == 0)
					|| (m_ptBoard->p[x2 + 1][y2 - 1] == 1 && m_ptBoard->p[x2 + 2][y2 - 2] == 0 && m_ptBoard->p[x2 + 3][y2 - 3] == 1 && m_ptBoard->p[x2 + 4][y2 - 4] == 0)) {
					three_0_x[0] = x2 - 1;
					three_0_y[0] = y2 + 1;
					if (m_ptBoard->p[x2 + 1][y2 - 1] == 0) {
						three_0_x[1] = x2 + 1; three_0_x[2] = x2 + 4;
						three_0_y[1] = y2 - 1; three_0_y[2] = y2 - 4;
					}
					if (m_ptBoard->p[x2 + 1][y2 - 1] == 1) {
						three_0_x[1] = x2 + 2; three_0_x[2] = x2 + 4;
						three_0_y[1] = y2 - 2; three_0_y[2] = y2 - 4;
					}
					three_forbid++;
					if (three_forbid > 1) {
						cout << endl << "黑方三三禁手！白方胜利！" << endl;
						three_forbid = 0;
						return true;
						break;
					}
				}
			}

			if (black_num == 3) {
				//四四禁手
				if (m_ptBoard->p[x2 - 3][y2 + 3] == 0 && m_ptBoard->p[x2 + 1][y2 - 1] == 0 &&
					m_ptBoard->p[x2 + 2][y2 - 2] == 1 && m_ptBoard->p[x2 + 3][y2 - 3] == 0) {
					four_0_x[3] = x2 - 3; four_0_x[4] = x2 + 1; four_0_x[5] = x2 + 3;
					four_0_y[3] = y2 + 3; four_0_y[4] = y2 - 1; four_0_y[5] = y2 - 3;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}//三三禁手
				else if (m_ptBoard->p[x2 - 3][y2 + 3] == 0 && m_ptBoard->p[x2 + 1][y2 - 1] == 0) {
					three_0_x[3] = x2 - 3; three_0_x[4] = x2 + 1;
					three_0_y[3] = y2 + 3; three_0_y[4] = y2 - 1;
					three_forbid++;
					if (three_forbid > 1) {
						cout << endl << "黑方三三禁手！白方胜利！" << endl;
						three_forbid = 0;
						return true;
						break;
					}
				}

			}

			//四四禁手
			if (black_num == 4) {
				if (m_ptBoard->p[x2 - 4][y2 + 4] == 0 && m_ptBoard->p[x2 + 1][y2 - 1] == 0) {
					four_0_x[6] = x2 - 4; four_0_x[7] = x2 + 1;
					four_0_y[6] = y2 + 4; four_0_y[7] = y2 - 1;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}
			}
			if (black_num == 2) {
				if (m_ptBoard->p[x2 - 2][y2 + 2] == 0 && m_ptBoard->p[x2 + 1][y2 - 1] == 0 &&
					m_ptBoard->p[x2 + 2][y2 - 2] == 1 && m_ptBoard->p[x2 + 3][y2 - 3] == 1 &&
					m_ptBoard->p[x2 + 4][y2 - 4] == 0) {
					four_0_x[8] = x2 - 2; four_0_x[9] = x2 + 1; four_0_x[10] = x2 + 4;
					four_0_y[8] = y2 + 2; four_0_y[9] = y2 - 1; four_0_y[10] = y2 - 4;
					four_forbid++;
					if (four_forbid > 1) {
						cout << endl << "黑方四四禁手！白方胜利！" << endl;
						four_forbid = 0;
						return true;
						break;
					}
				}
			}

			white_num = 0;
			if (black_num == 5)
			{
				if ((m_ptBoard->p[x2 + 1][y2 + 1] != 1) && (m_ptBoard->p[x2 + 1][y2 - 1] != -1)) {
					cout << endl << "黑方胜利！" << endl;
					return true;
					break;
				}
				else {
					cout << endl << "黑方长连禁手！白方胜利！" << endl;
					return true;
					break;
				}
			}
		}
		if ((m_ptBoard->p[x2][y2] == 2) || (m_ptBoard->p[x2][y2] == -2))
		{
			white_num++;
			black_num = 0;
			for (int j = 0; j < 11; j++)
				if (x2 == three_0_x[j] && y2 == three_0_y[j])
					three_forbid--;
			for (int k = 0; k < 5; k++)
				if (x2 == four_0_x[k] && y2 == four_0_y[k])
					four_forbid--;
			if (white_num == 5)
			{
				cout << endl << "白方胜利！" << endl;
				return true;
				break;
			}
		}
		x2++;
		y2--;
	}
	return false;
}