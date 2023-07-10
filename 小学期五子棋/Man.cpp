#include "Man.h"

void Man::init(Chess*chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	Chesspos pos;
	//ͨ������chess�������ж������Ƿ���Ч�����ӹ���
	while (1)
	{
		msg = GetMouseMsg();
		if (msg.uMsg == WM_LBUTTONDOWN && chess->clickBoard(msg.x, msg.y, &pos))
		{
			break;
		}
	}
	chess->ChessDown(&pos, CHESS_BLACK);
}
