#include "Board.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#define GetRowCol(__row, __col, __id) \
    int __row = _s[__id]._row;\
    int __col = _s[__id]._col
/*
 * 初始化棋盘的32颗棋子
 * 以及棋盘的布局
 * 和棋子选择的初始化
*/
Board::Board(QWidget *parent) : QFrame(parent)
{
    this->_r = 33;	//设置棋子的半径大小
    setMinimumSize(_r*18+1, _r*20+1);	//设置整窗口的大小，这里设置了固定值
    setMaximumSize(_r*18+1, _r*20+1);
    init(true);	//初始化
}

void Board::init(bool bRedSide)
{
    for(int i=0; i<32; ++i)
    {
        _s[i].init(i);
    }
    if(bRedSide)
    {
        for(int i=0; i<32; ++i)
        {
            _s[i].rotate();
        }
    }

    _selectid = -1;
    _bRedTurn = true;
    _bSide = bRedSide;
    update();
}

/*通过paintor来绘画整个棋盘上的棋子*/
void Board::paintEvent(QPaintEvent *)
{
    int r = height()/20;
    _r = r;
    _off = QPoint(r+1, r+1);

    QPainter p(this);
    //QPainter painter(this);

    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    p.save();
    drawPlate(p);
    p.restore();

    p.save();
    drawPlace(p);
    p.restore();

    p.save();
    drawInitPosition(p);
    p.restore();

    p.save();

    drawStone(p);

    //jiang jun
    if(Jiangjun == 1)   //if jiangjun == 1,it mean this step will eat your boss
    {
        Jiangjun = 0;   //change the old value
        QRect boundingRect;
        QFont font = p.font();
        font.setPixelSize(_r*1.51);//50
        p.setFont(font);
        p.setPen(QColor(255,0,0));// Qt::yellow
        const QRect rectangle2 = QRect(_r*7.42, _r*8.78, _r*6.1, _r*3.1);//245, 290, 200, 100
        p.drawText(rectangle2, 0, tr("将 军"), &boundingRect);

    }

    p.restore();
}

void Board::drawStone(QPainter &p) //32颗棋子
{
    for(int i=0; i<32; i++)
    {

        drawStone(p, i);

    }
}

bool Board::isDead(int id)
{
    if(id == -1)
    {
        return true;
    }
    return _s[id]._dead;
}

void Board::drawStone(QPainter &p, int id)
{
    if(isDead(id))
    {
        return;
    }

    QColor color;
    if(red(id)) color = Qt::red;
    else color = Qt::black;

    p.setPen(QPen(QBrush(color), 2));

    if(id == _selectid) p.setBrush(Qt::yellow);
    else p.setBrush(QColor(158,255,205));//54,180,199 15,226,247

    p.drawEllipse(cell(id));

    p.setFont(QFont("system", _r*1.2, 700));
    p.drawText(cell(id), name(id), QTextOption(Qt::AlignCenter));



}

QString Board::name(int id)
{
    return _s[id].name();
}

/*判断是我方的棋子还是敌方的棋子
 * 根据移动棋子的ID进行判断
 * id<16表示红色的一方
*/
bool Board::red(int id)
{
    return _s[id]._red;
}

void Board::drawInitPosition(QPainter &p, int row, int col)
{
    QPoint pt = center(row, col);
    QPoint off = QPoint(_r/6, _r/6);
    int len = _r/3;

    QPoint ptStart;
    QPoint ptEnd;

    if(col != 0)
    {
        /* 左上角 */
        ptStart = QPoint(pt.x() - off.x(), pt.y() - off.y());
        ptEnd = ptStart + QPoint(-len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, -len);
        p.drawLine(ptStart, ptEnd);

        /* 左下角 */
        ptStart = QPoint(pt.x() - off.x(), pt.y() + off.y());
        ptEnd = ptStart + QPoint(-len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, +len);
        p.drawLine(ptStart, ptEnd);
    }

    if(col != 8)
    {
        /* 右下角 */
        ptStart = QPoint(pt.x() + off.x(), pt.y() + off.y());
        ptEnd = ptStart + QPoint(+len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, +len);
        p.drawLine(ptStart, ptEnd);

        /* 右上角 */
        ptStart = QPoint(pt.x() + off.x(), pt.y() - off.y());
        ptEnd = ptStart + QPoint(+len, 0);
        p.drawLine(ptStart, ptEnd);
        ptEnd = ptStart + QPoint(0, -len);
        p.drawLine(ptStart, ptEnd);
    }
}

void Board::drawInitPosition(QPainter &p)
{
    drawInitPosition(p, 3, 0);
    drawInitPosition(p, 3, 2);
    drawInitPosition(p, 3, 4);
    drawInitPosition(p, 3, 6);
    drawInitPosition(p, 3, 8);

    drawInitPosition(p, 6, 0);
    drawInitPosition(p, 6, 2);
    drawInitPosition(p, 6, 4);
    drawInitPosition(p, 6, 6);
    drawInitPosition(p, 6, 8);

    drawInitPosition(p, 2, 1);
    drawInitPosition(p, 2, 7);

    drawInitPosition(p, 7, 1);
    drawInitPosition(p, 7, 7);
}

void Board::drawPlace(QPainter &p)
{
    p.drawLine(center(0, 3), center(2, 5));
    p.drawLine(center(2, 3), center(0, 5));

    p.drawLine(center(9, 3), center(7, 5));
    p.drawLine(center(7, 3), center(9, 5));
}

void Board::drawPlate(QPainter &p)
{
    for(int i=0; i<10; ++i)
    {
        if(i==0 || i==9)
        {
            p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
        }
        else
        {
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        }
        p.drawLine(center(i, 0), center(i, 8));
    }

    for(int i=0; i<9; ++i)
    {
        if(i==0 || i==8)
        {
            p.setPen(QPen(Qt::black, 3, Qt::SolidLine));
            p.drawLine(center(0, i), center(9, i));
        }
        else
        {
            p.setPen(QPen(Qt::black, 1, Qt::SolidLine));
            p.drawLine(center(0, i), center(4, i));
            p.drawLine(center(5, i), center(9, i));
        }
    }

    /*画 楚河 和 汉界*/
    QFont font = p.font();
    font.setPixelSize(_r*1.51);
    p.setFont(font);
    const QRect rectangle = QRect(_r*2.42, _r*8.78, _r*6.1, _r*3.1);//前两个参数是位置，后连个参数是Rect的大小
    QRect boundingRect;
    p.drawText(rectangle, 0, tr("楚 河"), &boundingRect);

    const QRect rectangle1 = QRect(_r*12.42, _r*8.78, _r*6.1, _r*3.1);
    p.drawText(rectangle1, 0, tr("汉 界"), &boundingRect);
}

QPoint Board::center(int row, int col)
{
    QPoint pt(_r*col*2, _r*row*2);
    return pt + _off;
}

QPoint Board::center(int id)
{
    return center(_s[id]._row, _s[id]._col);
}

QPoint Board::topLeft(int row, int col)
{
    return center(row, col) - QPoint(_r, _r);
}

QPoint Board::topLeft(int id)
{
    return center(id) - QPoint(_r, _r);
}

QRect Board::cell(int row, int col)
{
    return QRect(topLeft(row, col), QSize(_r*2-1, _r*2-1));
}

QRect Board::cell(int id)
{
    return QRect(topLeft(id), QSize(_r*2-1, _r*2-1));
}

/*
 * 这里是通过判断鼠标点击的位置, 然后决定归那个区域管制,计算的是鼠标点
 * 击的点和对应棋盘上的行和列的交点之间的距离，然后再将这个距离拿来和棋
 * 子的半径作比较,如果小于棋子的半径，那说明点击的是,棋子，如果大于此半
 * 径，则没有点击对应的棋子, PT为鼠标点击的像素坐标，row和col 分别为棋
 * 盘上画的线的行和列
*/
bool Board::getClickRowCol(QPoint pt, int &row, int &col)
{
    for(row=0; row<=9; ++row)
    {
        for(col=0; col<=8; ++col)
        {
            QPoint distance = center(row, col) - pt;//取出行列对应的中心点，然后去计算距离 勾股定理
            if(distance.x() * distance.x() + distance.y() * distance.y() < _r * _r)
                return true;
        }
    }
    return false;
}

void Board::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() != Qt::LeftButton)
    {
        return;
    }

    click(ev->pos());
}

bool Board::canSelect(int id)
{
    return _bRedTurn == _s[id]._red;
}

//试着选棋子，判断条件是否满足
void Board::trySelectStone(int id)
{
    if(id == -1)
        return;

    if(!canSelect(id)) return;

    _selectid = id;
    update();
}
//同一中颜色，要换棋子
bool Board::sameColor(int id1, int id2)
{
    if(id1 == -1 || id2 == -1) return false;

    return red(id1) == red(id2);
}

void Board::tryMoveStone(int killid, int row, int col)
{
    if(killid != -1 && sameColor(killid, _selectid))
    {
        trySelectStone(killid);
        return;
    }

    bool ret = canMove(_selectid, killid, row, col);
    if(ret)
    {
        moveStone(_selectid, killid, row, col);
        _selectid = -1;
        update();
    }
}

/*
 * 计算即将moveid棋子与鼠标点击的同行或者同列有几颗棋子,
 * 不在同一行或同一列上，默认返回值为-1
*/
int Board::getStoneCountAtLine(int row1, int col1, int row2, int col2)
{
    int ret = 0;//定义ret为棋子的个数
    if(row1 != row2 && col1 != col2)//不再同一行或者同一列，都返回false
        return -1;
    if(row1 == row2 && col1 == col2)
        return -1;

    if(row1 == row2)
    {
        int min = col1 < col2 ? col1 : col2;
        int max = col1 < col2 ? col2 : col1;
        for(int col = min+1; col<max; ++col)
        {
            if(getStoneId(row1, col) != -1) ++ret;
        }
    }
    else
    {
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for(int row = min+1; row<max; ++row)
        {
            if(getStoneId(row, col1) != -1) ++ret;
        }
    }
    return ret;
}

/* 求棋盘上的行列值和鼠标点击的的行列的关系值*/
int Board::relation(int row1, int col1, int row, int col)
{
    return qAbs(row1-row)*10+qAbs(col1-col);
}

//适合车 炮 兵
int Board::Check_Jiangjun(int moveid,int row,int col)
{
    if(moveid<16)//red stone
    {
        int ret = getStoneCountAtLine(_s[20]._row, _s[20]._col, row, col);
        int ret2 = getStoneCountAtLine(_s[20]._row, _s[20]._col,_s[moveid]._row, _s[moveid]._col);
        if(ret2 == 0 )
        {
            return --ret;
        }
        return ret;
    }
    else//black stone moveid > 16
    {
        //先计算鼠标点击的点的位置和对方的boss位置之间的棋子个数，满足则将军
        int ret = getStoneCountAtLine(_s[4]._row, _s[4]._col, row, col);
        //先计算鼠标点击的点的位置和对方的boss位置之间的棋子个数，满足则将军 下同
        int ret2 = getStoneCountAtLine(_s[4]._row, _s[4]._col,_s[moveid]._row, _s[moveid]._col);
        if(ret2 == 0 )
        {
            return --ret;
        }
        return ret;
    }
}
/*车：
 * 只能走直线，要吃棋子的时候，
 * 中间不能有其他棋子，遇到将的时候，可以吃将，也就是将军
*/
bool Board::canMoveChe(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int ret = getStoneCountAtLine(row1, col1, row, col);
    //如果车走的这条线上棋子的个数为0且老爷也再这里的行和列上 则将军
    if(Check_Jiangjun(moveid,row,col)==0)
    {
        Jiangjun = 1;
    }
    if(ret == 0)
    {
        return true;
    }
    return false;
}

int Board::Ma_jiang_jun(int moveid, int row, int col)
{
    if(moveid<16)//red stone
    {
        int ret = relation(_s[20]._row, _s[20]._col, row, col);//点击的点和boss之间的关系
        return ret;
    }
    else//black stone moveid > 16
    {
        int ret = relation(_s[4]._row, _s[4]._col, row, col);//点击的点和boss之间的关系
        return ret;
    }
}
/*检查马落下后，下一步马可以走棋子的地方的是否为将，若是 则将军
 * 这里通过计算马下一步可以走的地方的八颗棋子，
 * 并且选择的棋子的颜色要和将的颜色不一样
 * 马周围的这个点都是对称的所以只需要计算4个点
 * 下面的图就是马周围下一步马可以走棋的地方:
 *    1  2
 * 8        3
 *     马
 * 7        4
 *    6  5
 * 在此过程中还要注意下一步的马是否憋马脚!
 *     11
 * 22  马  33
 *     44
 * 马走日字，还要注意憋马脚，马脚是在马的同一边
*/
bool Board::canMoveMa(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);    
    if(r != 12 && r != 21)
        return false;

    if(r == 12)
    {
        if(getStoneId(row1, (col+col1)/2) != -1)//憋马脚
        {
            return false;
        }
        if(Ma_jiang_jun(moveid,row,col)==12||Ma_jiang_jun(moveid,row,col)==21)
        {
            Jiangjun = 1;
        }
    }
    else
    {
        if(getStoneId((row+row1)/2, col1) != -1)
        {
            return false;
        }
        if(Ma_jiang_jun(moveid,row,col)==12||Ma_jiang_jun(moveid,row,col)==21)
        {
            Jiangjun = 1;
        }
    }

    return true;
}
/*炮：
 * ret == 0，炮只能移动，不可吃棋
 * ret == 1,且killid为敌方的，可以进行吃起棋
*/
bool Board::canMovePao(int moveid, int killid, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int ret = getStoneCountAtLine(row, col, row1, col1);
    //如果这个之间有一个棋子，则将军
    if(Check_Jiangjun(moveid,row,col)==1)
    {
        Jiangjun = 1;
    }
    if(killid != -1)
    {
        if(ret == 1) return true;
    }
    else
    {
        if(ret == 0) return true;
    }
    return false;
}

bool Board::Bing_jiangjun(int moveid,int row, int col)
{
    //需要判断前 左 右是否的棋子是否是将，若是，则将军
    int jiangid;
    if(moveid<16)//移动的是红色的棋子
    {
        jiangid=20;
    }
    else
    {
        jiangid=4;
    }

    if(row == _s[jiangid]._row && col+1 == _s[jiangid]._col)
    {
        return true;
    }
    else if(row == _s[jiangid]._row && col-1 == _s[jiangid]._col)
    {
        return true;
    }
    else if(row+1 == _s[jiangid]._row && col == _s[jiangid]._col)
    {
        return true;
    }
    else if(row-1 == _s[jiangid]._row && col == _s[jiangid]._col)
    {
        return true;
    }

    return false;
}

bool Board::canMoveBing(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 1 && r != 10) return false;

    if(isBottomSide(moveid))//过河前 不能横这走
    {
        if(row > row1) return false;
        if(row1 >= 5 && row == row1) return false;
    }
    else    //过河后  保证不能再向后走
    {
        if(row < row1) return false;
        if(row1 <= 4 && row == row1) return false;
    }
    if(Bing_jiangjun(moveid,row,col))
    {
        Jiangjun = 1;
    }

    return true;
}

/*将:
 * 只能在九宫格中,
 * 移动的长度只能移动一格
 * 两个将不能对面
*/
bool Board::canMoveJiang(int moveid, int killid, int row, int col)
{
    if(killid != -1 && _s[killid]._type == Stone::JIANG)
    {
        return canMoveChe(moveid, killid, row, col);
    }
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 1 && r != 10) //将只能一次移动一步。所以，行或这个列的差值中的一个必定为0或者10
    {
        return false;
    }

    if(col < 3 || col > 5)
    {
        return false;
    }
    if(isBottomSide(moveid))//isBottomSide,将必须要在大于第七条线的范围活动
    {
        if(row < 7) return false;
    }
    else    //反之 将超过了第2条线后,就不能移动
    {
        if(row > 2) return false;
    }
    return true;
}

bool Board::canMoveShi(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 11) return false;

    if(col < 3 || col > 5) return false;
    if(isBottomSide(moveid))    //isBottomSide
    {
        if(row < 7) return false;
    }
    else    //isupper
    {
        if(row > 2) return false;
    }
    return true;
}

/*象：
 * 只能以田字格的方式进行移动，当田字中心有棋子的时候
 * 不能移动，且不能过界，只能在自己的一方进行移动
*/
bool Board::canMoveXiang(int moveid, int, int row, int col)
{
    GetRowCol(row1, col1, moveid);
    int r = relation(row1, col1, row, col);
    if(r != 22) return false;

    int rEye = (row+row1)/2;
    int cEye = (col+col1)/2;
    if(getStoneId(rEye, cEye) != -1)//计算象眼
        return false;   //如果象眼上面有棋子，则返回该棋子的id否则，返回-1

    if(isBottomSide(moveid))
    {
        if(row < 4) return false;//只要行数<4之后，就说明越界了，返回false
    }
    else
    {
        if(row > 5) return false;//只要行数>5之后，就说明越界了，返回false
    }
    return true;
}

/*能不能移动棋子:
 * 第一,若是moveid和killid的颜色相同,则不能移动棋子
 * 第二:换选择
*/
bool Board::canMove(int moveid, int killid, int row, int col)
{
    if(sameColor(moveid, killid)) return false;

    switch (_s[moveid]._type)
    {
    case Stone::CHE:
        return canMoveChe(moveid, killid, row, col);

    case Stone::MA:
        return canMoveMa(moveid, killid, row, col);

    case Stone::PAO:
        return canMovePao(moveid, killid, row, col);

    case Stone::BING:
        return canMoveBing(moveid, killid, row, col);

    case Stone::JIANG:
        return canMoveJiang(moveid, killid, row, col);

    case Stone::SHI:
        return canMoveShi(moveid, killid, row, col);

    case Stone::XIANG:
        return canMoveXiang(moveid, killid, row, col);

    }
    return false;
}

void Board::reliveStone(int id)
{
    if(id==-1) return;  //is space
    _s[id]._dead = false;   //is dead
}

void Board::killStone(int id)
{
    if(id==-1) return;
    _s[id]._dead = true;
}

bool Board::isBottomSide(int id)
{
    return _bSide == _s[id]._red;
}

void Board::moveStone(int moveid, int row, int col)
{
    _s[moveid]._row = row;  //吧点击的行和列进行更新
    _s[moveid]._col = col;

    _bRedTurn = !_bRedTurn;//就需要交换选择
}
//保存步骤
void Board::saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps)
{
    GetRowCol(row1, col1, moveid);
    Step* step = new Step;
    step->_colFrom = col1;//分别吧点击的棋子和走的棋子 的行和列记录下来
    step->_colTo = col;
    step->_rowFrom = row1;
    step->_rowTo = row;
    step->_moveid = moveid; //移动的棋子
    step->_killid = killid; //要吃掉的棋子

    steps.append(step); //在后面进行追加
}
//移动棋子
void Board::moveStone(int moveid, int killid, int row, int col)
{
    saveStep(moveid, killid, row, col, _steps);//移动棋子之前 先保存下步骤
    //然后进行吃棋子和杀棋子
    killStone(killid);
    moveStone(moveid, row, col);
}

void Board::click(int id, int row, int col)
{
    if(this->_selectid == -1)
    {
        trySelectStone(id);
    }
    else
    {
        tryMoveStone(id, row, col);
    }
}

void Board::click(QPoint pt)
{
    int row, col;
    bool bClicked = getClickRowCol(pt, row, col);
    if(!bClicked) return;

    int id = getStoneId(row, col);
    click(id, row, col);
}

/*确定某个行列位置上是否是棋子:
 * 输入一个行列坐标后遍历所有存活的棋子的行列坐标
 * 看一下有没有棋子与之完全吻合，若存在这样的棋子
 * 则表示该行列坐标上存在棋子。如果id有棋子，则返
 * 回该棋子的id否则，返回-1
*/
int Board::getStoneId(int row, int col)
{
    for(int i=0; i<32; ++i)
    {
        if(_s[i]._row == row && _s[i]._col == col && !isDead(i))
            return i;
    }
    return -1;
}

void Board::back(Step *step)
{
    reliveStone(step->_killid);
    moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}

//返回一步
void Board::backOne()
{
    if(this->_steps.size() == 0) return;

    Step* step = this->_steps.last();
    _steps.removeLast();
    back(step);

    update();
    delete step;
}

void Board::back()
{
    backOne();
}

void Board::slotBack()
{
    back();
}

Board::~Board()
{

}
