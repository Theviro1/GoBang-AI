#include "AI.h"

void AI::init(Chess*chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++)
	{
		vector<int> row;
		for (int j = 0; j < size; j++)
		{
			row.push_back(0);
		}
		scoreMap.push_back(row);
	}
}

void AI::go()
{
	Chesspos pos = think();
	Sleep(1000);//加停顿以示尊敬
	chess->ChessDown(&pos, CHESS_WHITE);
}

void AI::calculateScore()
{
	int personNum=0;//玩家有多少个连续棋子
	int aiNum=0;//ai有多少个连续棋子
	int emptyNum = 0;//有多少个空白位置
	for (int i = 0; i < scoreMap.size(); i++)
	{
		for (int j = 0; j < scoreMap[i].size(); j++)
		{
			scoreMap[i][j] = 0;
		}
	}
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			personNum = 0;
			aiNum = 0;
			emptyNum = 0;
			//对每个点进行评分计算
			if (chess->getChessData(row, col)) continue;//点是空的就继续

			//实现方向判断，由-1和1代表上下和左右，0代表坐标不变
			//计算四个方向的正反向
			for (int y = -1; y <= 0; y++)
			{
				for (int x = -1; x <= 1; x++)
				{
					if (x == 0 && y == 0) continue;
					if (y == 0 && x != 1) continue;//第四个方向y=0 x=1
					personNum = 0;
					aiNum = 0;
					emptyNum = 0;
					//假设玩家在此处落子
					//正向
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;
						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1)
						{
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else break;
					}
					//反向
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;
						if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 1)
						{
							personNum++;
						}
						else if (curRow >= 0 && curRow < size &&
							curCol >= 0 && curCol < size &&
							chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else break;
					}
					//价值计算
					if (personNum == 1) scoreMap[row][col] += 10;
					else if (personNum == 2)
					{
						if (emptyNum == 1) scoreMap[row][col] += 30;
						else if(emptyNum == 2) scoreMap[row][col] += 40;
					}
					else if (personNum == 3)
					{
						if(emptyNum==1) scoreMap[row][col] += 60;
						else if(emptyNum==2) scoreMap[row][col] += 200;
					}
					else if (personNum >= 4) scoreMap[row][col] += 20000;

					//假设ai在此处落子
					emptyNum = 0;
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row + i * y;
						int curCol = col + i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == -1)
						{
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else break;
					}
					for (int i = 1; i <= 4; i++)
					{
						int curRow = row - i * y;
						int curCol = col - i * x;

						if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == -1)
						{
							aiNum++;
						}
						else if (curRow >= 0 && curRow < size && curCol >= 0 && curCol < size
							&& chess->getChessData(curRow, curCol) == 0)
						{
							emptyNum++;
							break;
						}
						else break;
					}
					if (aiNum == 0) scoreMap[row][col] += 5;
					else if (aiNum == 1) scoreMap[row][col] += 10;
					else if (aiNum == 2)
					{
						if (emptyNum == 1) scoreMap[row][col] += 25;
						else if (emptyNum == 2) scoreMap[row][col] += 50;
					}
					else if (aiNum == 3)
					{
						if (emptyNum == 1) scoreMap[row][col] +=55 ;
						else if (emptyNum == 2) scoreMap[row][col] += 10000;
					}
					else if (aiNum >= 4) scoreMap[row][col] += 30000;
				}
			}
		}
	}
}

Chesspos AI::think()
{
	calculateScore();
	vector<Chesspos> maxpoints;//找最大的各个点的评分存入到数组里
	int maxscore = 0;
	int size = chess->getGradeSize();
	for (int row = 0; row < size; row++)
	{
		for (int col = 0; col < size; col++)
		{
			if (chess->getChessData(row, col) == 0)
			{
				if (scoreMap[row][col] > maxscore)
				{
					maxscore = scoreMap[row][col];
					maxpoints.clear();//遇到更大的点就把数组清空
					maxpoints.push_back(Chesspos(row, col));
				}
				else if (scoreMap[row][col] == maxscore)//一样大的点都放入数组
				{
					maxpoints.push_back(Chesspos(row,col));
				}
			}
		}
	}
	int index = rand() % maxpoints.size();//在这个数组里随机抽取一个最大评分的点
	return maxpoints[index];
}
