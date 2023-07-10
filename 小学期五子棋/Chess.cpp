#include "Chess.h"
#include<math.h>
#include<mmsystem.h>
#include<conio.h>
#pragma comment(lib,"winmm.lib")

void putimagePNG(int x, int y, IMAGE* picture) //xΪ����ͼƬ��X���꣬yΪY����
{
    // ������ʼ��
    DWORD* dst = GetImageBuffer();    // GetImageBuffer()���������ڻ�ȡ��ͼ�豸���Դ�ָ�룬EASYX�Դ�
    DWORD* draw = GetImageBuffer();
    DWORD* src = GetImageBuffer(picture); //��ȡpicture���Դ�ָ��
    int picture_width = picture->getwidth(); //��ȡpicture�Ŀ�ȣ�EASYX�Դ�
    int picture_height = picture->getheight(); //��ȡpicture�ĸ߶ȣ�EASYX�Դ�
    int graphWidth = getwidth();       //��ȡ��ͼ���Ŀ�ȣ�EASYX�Դ�
    int graphHeight = getheight();     //��ȡ��ͼ���ĸ߶ȣ�EASYX�Դ�
    int dstX = 0;    //���Դ������صĽǱ�

    // ʵ��͸����ͼ ��ʽ�� Cp=��p*FP+(1-��p)*BP �� ��Ҷ˹���������е���ɫ�ĸ��ʼ���
    for (int iy = 0; iy < picture_height; iy++)
    {
        for (int ix = 0; ix < picture_width; ix++)
        {
            int srcX = ix + iy * picture_width; //���Դ������صĽǱ�
            int sa = ((src[srcX] & 0xff000000) >> 24); //0xAArrggbb;AA��͸����
            int sr = ((src[srcX] & 0xff0000) >> 16); //��ȡRGB���R
            int sg = ((src[srcX] & 0xff00) >> 8);   //G
            int sb = src[srcX] & 0xff;              //B
            if (ix >= 0 && ix <= graphWidth && iy >= 0 && iy <= graphHeight && dstX <= graphWidth * graphHeight)
            {
                dstX = (ix + x) + (iy + y) * graphWidth; //���Դ������صĽǱ�
                int dr = ((dst[dstX] & 0xff0000) >> 16);
                int dg = ((dst[dstX] & 0xff00) >> 8);
                int db = dst[dstX] & 0xff;
                draw[dstX] = ((sr * sa / 255 + dr * (255 - sa) / 255) << 16)  //��ʽ�� Cp=��p*FP+(1-��p)*BP  �� ��p=sa/255 , FP=sr , BP=dr
                    | ((sg * sa / 255 + dg * (255 - sa) / 255) << 8)         //��p=sa/255 , FP=sg , BP=dg
                    | (sb * sa / 255 + db * (255 - sa) / 255);              //��p=sa/255 , FP=sb , BP=db
            }
        }
    }
}
Chess::Chess(int gradeSize, int marginX, int marginY, float chessSize)
{
    this->gradeSize = gradeSize;
    this->margin_x = marginX;
    this->margin_y = marginY;
    this->chessSize = chessSize;
    playerFlag = CHESS_BLACK;
    for (int i = 0; i < gradeSize; i++)
    {
        vector<int> row;
        for (int j = 0; j < gradeSize; j++)
        {
            row.push_back(0);
        }
        chessMap.push_back(row);
    }
}

void Chess::init()
{
    initgraph(897, 895);
    loadimage(0, L"res/����2.jpg");
    mciSendString(L"play res/start.wav", 0, 0, 0);
    loadimage(&ChessBlackImg, L"res/black.png", chessSize, chessSize, true);
    loadimage(&ChessWhiteImg, L"res/white.png", chessSize, chessSize, true);
    for (int i = 0; i < gradeSize; i++)
    {
        for (int j = 0; j < gradeSize; j++) chessMap[i][j] = 0;
    }
    playerFlag = true;
}

bool Chess::clickBoard(int x, int y, Chesspos* pos)
{
    int col = (x - margin_x) / chessSize;
    int row = (y - margin_y) / chessSize;
    int leftTopposX = margin_x + col * chessSize;
    int leftTopposY = margin_y + row * chessSize;
    bool ret = false;
    int offset = chessSize * 0.4;
    int len;
    do {
        //���Ͻ�
        len = sqrt((x - leftTopposX) * (x - leftTopposX) + (y - leftTopposY) * (y - leftTopposY));
        if (len < offset)
        {
            pos->row = row;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0) ret = true;
            break;
        }
        //���Ͻ�
        int x2 = leftTopposX + chessSize;
        int y2 = leftTopposY;
        len = sqrt((x-x2)*(x-x2)+(y-y2)*(y-y2));
        if (len < offset)
        {
            pos->row = row;
            pos->col = col+1;
            if (chessMap[pos->row][pos->col] == 0) ret = true;
            break;
        }
        //���½�
        int x3 = leftTopposX;
        int y3 = leftTopposY + chessSize;
        len = sqrt((x - x3) * (x - x3) + (y - y3) * (y - y3));
        if (len < offset)
        {
            pos->row = row+1;
            pos->col = col;
            if (chessMap[pos->row][pos->col] == 0) ret = true;
            break;
        }
        //���½�
        int x4 = leftTopposX + chessSize;
        int y4 = leftTopposY + chessSize;
        len = sqrt((x - x4) * (x - x4) + (y - y4) * (y - y4));
        if (len < offset)
        {
            pos->row = row + 1;
            pos->col = col + 1;
            if (chessMap[pos->row][pos->col] == 0) ret = true;
            break;
        }

        return ret;
    } while (0);
    
   
}

void Chess::ChessDown(Chesspos* pos, Chess_kind_t kind)
{
    mciSendString(L"play res/down7.WAV", 0, 0, 0);
    int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
    int y = margin_y + chessSize * pos->row - 0.5 * chessSize;
    if (kind == CHESS_WHITE)
    {
        putimagePNG(x, y, &ChessWhiteImg);
    }
    else 
    {
        putimagePNG(x, y, &ChessBlackImg);
    }
    updateGamemap(pos);
}

int Chess::getGradeSize()
{
    return gradeSize;
}

bool Chess::checkOver()
{
    if (checkWin())
    {
        Sleep(1000);//ʤ������ͣ1��
        if (playerFlag == false)//����������Ǻ���
        {
            mciSendString(L"play res/����.MP3", 0, 0, 0);
            loadimage(0, L"res/ʤ��.jpg");
        }
        else
        {
            mciSendString(L"play res/ʧ��.MP3", 0, 0, 0);
            loadimage(0, L"res/ʧ��.jpg");
        }
        _getch();//��ͣ���� ����������� conio.h
        return true;
    }
    return false;
}

void Chess::updateGamemap(Chesspos*pos)
{
    lastPos = *pos;
    chessMap[pos->row][pos->col] = playerFlag ? CHESS_BLACK : CHESS_WHITE;
    playerFlag = !playerFlag;
}

int Chess::getChessData(Chesspos* pos)
{
    return chessMap[pos->row][pos->col];
}

int Chess::getChessData(int row, int col)
{
    return chessMap[row][col];
}

bool Chess::checkWin()
{
    //���ӵ�λ��
    int row = lastPos.row;
    int col = lastPos.col;
    //���ӵ��ˮƽ�����ж�
    for (int i = 0; i < 5; i++)
    {
        if (col - i >= 0 && col - i + 4 < gradeSize &&
            chessMap[row][col - i] == chessMap[row][col - i + 1] &&
            chessMap[row][col - i] == chessMap[row][col - i + 2] &&
            chessMap[row][col - i] == chessMap[row][col - i + 3] &&
            chessMap[row][col - i] == chessMap[row][col - i + 4]
            )  return true;
    }
    //���ӵ�Ĵ�ֱ�����ж�
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 && row - i + 4 < gradeSize &&
            chessMap[row-i][col] == chessMap[row-i+1][col] &&
            chessMap[row-i][col] == chessMap[row-i+2][col] &&
            chessMap[row-i][col] == chessMap[row-i+3][col] &&
            chessMap[row-i][col] == chessMap[row-i+4][col]
            )  return true;
    }
    //���ӵ��б�����ж�
    for (int i = 0; i < 5; i++)
    {
        if (row + i - 4>= 0 && row + i < gradeSize && col - i >= 0 && col - i + 4 < gradeSize &&
            chessMap[row + i][col - i] == chessMap[row + i - 1][col - i + 1] &&
            chessMap[row + i][col - i] == chessMap[row + i - 2][col - i + 2] &&
            chessMap[row + i][col - i] == chessMap[row + i - 3][col - i + 3] &&
            chessMap[row + i][col - i] == chessMap[row + i - 4][col - i + 4]
            ) return true;
    }
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 && row - i + 4 < gradeSize && col - i >= 0 && col - i + 4 < gradeSize &&
            chessMap[row - i][col - i] == chessMap[row - i + 1][col - i + 1] &&
            chessMap[row - i][col - i] == chessMap[row - i + 2][col - i + 2] &&
            chessMap[row - i][col - i] == chessMap[row - i + 3][col - i + 3] &&
            chessMap[row - i][col - i] == chessMap[row - i + 4][col - i + 4]
            ) return true;
    }
    return false;
}
