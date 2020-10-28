#ifndef BOARD_H
#define BOARD_H

#include <QFrame>
#include "Stone.h"
#include "Step.h"
#include <QVector>

class Board : public QFrame
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    ~Board();
    /* 游戏项目的数据*/
    Stone _s[32];
    int _r;
    QPoint _off;
    bool _bSide;
    int Jiangjun=0;

    QVector<Step*> _steps;

    /* 游戏的状态 */
    int _selectid;  //选择棋子的id
    bool _bRedTurn; //棋子换玩家
    void init(bool bRedSide);	//初始化红色这一边的棋子

    /* 画棋盘、棋子、函数 */
    void paintEvent(QPaintEvent *);
    void drawPlate(QPainter& p);
    void drawPlace(QPainter& p);
    void drawInitPosition(QPainter& p);	//初始化的位置
    void drawInitPosition(QPainter& p, int row, int col);
    void drawStone(QPainter& p);	//画棋子
    void drawStone(QPainter& p, int id);	//重构函数

    /* 这些函数是一些小的功能函数转换 */
    QPoint center(int row, int col);	
    QPoint center(int id);	//同为重构函数
    QPoint topLeft(int row, int col);
    QPoint topLeft(int id);
    QRect cell(int row, int col);	
    QRect cell(int id);
    bool getClickRowCol(QPoint pt, int& row, int& col);//获取这一点的行和列
    int Check_Jiangjun(int moveid,int row,int col);
    int Ma_jiang_jun(int moveid, int row, int col);
    bool Bing_jiangjun(int moveid,int row, int col);

    QString name(int id);
    bool red(int id);	//这个棋子是否是红色
    bool sameColor(int id1, int id2);	//比较两个棋子的颜色是否是相同的
    int getStoneId(int row, int col);	//获得棋子的id号
    void killStone(int id);	//吃棋子函数
    void reliveStone(int id);	//在同一个颜色下的棋子，进行选棋
    void moveStone(int moveid, int row, int col);	//移动棋子
    bool isDead(int id);	//检测该棋子是否已经被吃掉

    /* 移动棋子 */
    void mouseReleaseEvent(QMouseEvent *);	//鼠标点击事件
    void click(QPoint pt);	//鼠标点击
    virtual void click(int id, int row, int col);	//虚函数click
    void trySelectStone(int id);	//选棋子
    void tryMoveStone(int killid, int row, int col);	//试着移动棋子，判断是否可以移动
    void moveStone(int moveid, int killid, int row, int col);	//移动棋子
    void saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps);	//保存步骤
    void backOne();	//返回一步

    void back(Step* step);

    virtual void back();

    /* 棋子的规则 */
    bool canMove(int moveid, int killid, int row, int col);	//能否移动棋子
    bool canMoveChe(int moveid, int killid, int row, int col);	//能否移动车
    bool canMoveMa(int moveid, int killid, int row, int col);	//能否移动马
    bool canMovePao(int moveid, int killid, int row, int col);	//能否移动炮
    bool canMoveBing(int moveid, int killid, int row, int col);	//能否移动兵
    bool canMoveJiang(int moveid, int killid, int row, int col);	//能否移动将
    bool canMoveShi(int moveid, int killid, int row, int col);	//能否移动士
    bool canMoveXiang(int moveid, int killid, int row, int col);	//能否移动象
    bool canSelect(int id);	//能否选择棋子

    /* 辅助规则的一些函数 */
    int getStoneCountAtLine(int row1, int col1, int row2, int col2);	//计算同一行中的棋子个数
    int relation(int row1, int col1, int row, int col);	//计算两个点之间的关系值，这里是用来判断棋子能否进行吃棋子的关键
    bool isBottomSide(int id);

signals:

public slots:
    void slotBack();

};

#endif // BOARD_H
