#pragma once
#include "Chess.h"

class AI
{
public:
	//��ʼ������
	void init(Chess*chess);
	//���Խ�������
	void go();

private:
	Chess* chess;
	vector<vector<int>> scoreMap;
private:
	void calculateScore();
	Chesspos think();
};

