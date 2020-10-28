#ifndef STONE_H
#define STONE_H

#include <QRect>
#include <QPainter>

//#pragma execution_character_set("utf-8")
class Stone
{
public:
    Stone();
    ~Stone();
	//枚举出棋子所以的棋子类型
    enum TYPE{CHE, MA, PAO, BING, JIANG, SHI, XIANG};

    void init(int id);//棋子的初始化

    int _row;	//定义棋子的行
    int _col;	//定义棋子的列
    TYPE _type;	//定义棋子的类型
    bool _dead;	//定义棋子的存活状态
    bool _red;	//定义棋子的颜色 是黑色还是红色
    int _id;	//定义棋子的id号 这里是从0到31号因为由32个棋子

    QString name();	//声明为棋子命名函数
	
    void rotate();	//声明旋转棋盘函数
};

#endif // STONE_H
