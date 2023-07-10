#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

struct Chesspos {
	int row;//行
	int col;//列
	Chesspos(int r = 0, int c = 0) :row(r), col(c) {};
};


typedef enum {
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}Chess_kind_t;

class Chess
{
public:
	Chess(int gradeSize, int marginX, int marginY, float chessSize);
	//初始化棋盘样式等基本数据
	void init();
	//判断点击是否有效，有效就把点击转换成Chesspos
	bool clickBoard(int x, int y, Chesspos* pos);
	//落子在Chesspos的位置上
	void ChessDown(Chesspos* pos, Chess_kind_t kind);
	//获取棋盘大小
	int getGradeSize();
	//检查棋局是否已经结束
	bool checkOver();
	//更新棋盘
	void updateGamemap(Chesspos*pos);
	//获取指定位置的棋子信息
	int getChessData(Chesspos* pos);
	int getChessData(int row, int col);
	bool checkWin();//胜负已分就返回true 否则返回false
private:
	IMAGE ChessBlackImg;
	IMAGE ChessWhiteImg;

	int gradeSize;//棋盘大小
	int margin_x;//左右边界距离
	int margin_y;//上下边界距离
	float chessSize;
	vector<vector<int>> chessMap;//0代表空，-1代表白子，1代表黑子
	bool playerFlag;//true代表改黑子走，flase代表该白子走
	Chesspos lastPos;
};

