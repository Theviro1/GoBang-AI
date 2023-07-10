#pragma once
#include "Chess.h"

class Man
{
public:
	//初始化玩家数据
	void init(Chess*chess);
	//进行操作
	void go();
private:
	Chess* chess;
};

