#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

struct Chesspos {
	int row;//��
	int col;//��
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
	//��ʼ��������ʽ�Ȼ�������
	void init();
	//�жϵ���Ƿ���Ч����Ч�Ͱѵ��ת����Chesspos
	bool clickBoard(int x, int y, Chesspos* pos);
	//������Chesspos��λ����
	void ChessDown(Chesspos* pos, Chess_kind_t kind);
	//��ȡ���̴�С
	int getGradeSize();
	//�������Ƿ��Ѿ�����
	bool checkOver();
	//��������
	void updateGamemap(Chesspos*pos);
	//��ȡָ��λ�õ�������Ϣ
	int getChessData(Chesspos* pos);
	int getChessData(int row, int col);
	bool checkWin();//ʤ���ѷ־ͷ���true ���򷵻�false
private:
	IMAGE ChessBlackImg;
	IMAGE ChessWhiteImg;

	int gradeSize;//���̴�С
	int margin_x;//���ұ߽����
	int margin_y;//���±߽����
	float chessSize;
	vector<vector<int>> chessMap;//0����գ�-1������ӣ�1�������
	bool playerFlag;//true����ĺ����ߣ�flase����ð�����
	Chesspos lastPos;
};

