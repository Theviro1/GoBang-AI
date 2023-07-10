#pragma once
#include "Chess.h"

class AI
{
public:
	//初始化电脑
	void init(Chess*chess);
	//电脑进行落子
	void go();

private:
	Chess* chess;
	vector<vector<int>> scoreMap;
private:
	void calculateScore();
	Chesspos think();
};

