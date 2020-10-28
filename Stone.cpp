#include "Stone.h"
#include <QDebug>

//#pragma execution_character_set("utf-8")
Stone::Stone()
{

}

Stone::~Stone()
{

}

/* 对画的棋子进行命名 */
QString Stone::name()
{
    switch(this->_type)
    {
    case CHE:
        return "車";
    case MA:
        return "马";
    case PAO:
        return "炮";
    case BING:
        return "兵";
    case JIANG:
        return "将";
    case SHI:
        return "士";
    case XIANG:
        return "相";
     }
    return "错误";
}

/* 棋子初始化 定义棋子的行和列以及类型 */
void Stone::init(int id)
{
    struct {
        int row, col;
        Stone::TYPE type;
    } pos[16] = {
    {0, 0, Stone::CHE},
    {0, 1, Stone::MA},
    {0, 2, Stone::XIANG},
    {0, 3, Stone::SHI},
    {0, 4, Stone::JIANG},
    {0, 5, Stone::SHI},
    {0, 6, Stone::XIANG},
    {0, 7, Stone::MA},
    {0, 8, Stone::CHE},

    {2, 1, Stone::PAO},
    {2, 7, Stone::PAO},
    {3, 0, Stone::BING},
    {3, 2, Stone::BING},
    {3, 4, Stone::BING},
    {3, 6, Stone::BING},
    {3, 8, Stone::BING},
    };

    if(id < 16)
    {
        this->_col = pos[id].col;
        this->_row = pos[id].row;
        this->_type = pos[id].type;
    }
    else
    {	
	/* 由于总的由8条横线9条竖线，上面的相当于一个二位数组 从{0 0}开始  */
        this->_col = 8-pos[id-16].col;
        this->_row = 9-pos[id-16].row;
        this->_type = pos[id-16].type;
    }

    this->_dead = false;	//初始化的是哈，所有的棋子都为活着的
    this->_red = id<16;		//将id小于16的棋子命名为红色
}

/* 由于网络对战还存在双方，而每一方都是需要自己的
颜色在靠近自己的一方，所以这里写了一个旋转棋盘的函数 */
void Stone::rotate()	
{
    this->_col = 8-this->_col;
    this->_row = 9-this->_row;
}
