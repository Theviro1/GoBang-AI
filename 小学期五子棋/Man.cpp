#include "Man.h"

void Man::init(Chess*chess)
{
	this->chess = chess;
}

void Man::go()
{
	MOUSEMSG msg;
	Chesspos pos;
	//通过调用chess对象来判断落子是否有效和落子功能
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
