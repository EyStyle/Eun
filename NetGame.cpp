#include "NetGame.h"

NetGame::NetGame(bool server, QWidget *parent) : Board(parent)
{
    _server = NULL;	//先置为空
    _socket = NULL;
    _bServer = server;	//由参数传递进来，到底谁是服务端还是客户端
	/*这里先判断用户点击的是服务端还是客服端，从而执行对应的函数*/
    if(_bServer)
    {
        _server = new QTcpServer(this);		//定义一个新的TCP服务作为服务端
        _server->listen(QHostAddress::Any, 9899);	//然后进行监听任意的IP地址，还要匹配端口号码
        connect(_server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));	//当监听到这个连接后，就执行后面的槽函数
    }
    else
    {
        _socket = new QTcpSocket(this);//同理，定义一个新的客户端
        //_socket->connectToHost(QHostAddress::Any, 9899);
         _socket->connectToHost(QHostAddress("127.0.0.1"), 9899);
        connect(_socket, SIGNAL(readyRead()), this, SLOT(slotDataArrive()));
    }
}
 /* 槽函数的实现*/
void NetGame::slotNewConnection()
{
    if(_socket) return;	//若过是客户端，就返回，

    _socket = _server->nextPendingConnection();	//服务端就持续进行连接
    connect(_socket, SIGNAL(readyRead()), this, SLOT(slotDataArrive()));	//读取信号，等待数据的到来

    /* 产生随机数来决定谁走红色 */
    bool bRedSide = qrand()%42>0;
    init(bRedSide);

    /* 发送给对方 */
    QByteArray buf;	//定义一个buf用于缓冲数据
    buf.append(1);
    buf.append(bRedSide?0:1);
    _socket->write(buf);	//将数据写进buf中
}

 /* 悔棋子函数*/
void NetGame::back()	
{
    if(_bRedTurn != _bSide)
        return;		//如果现在还没有轮到你下棋，则你不能执行悔棋操作
    backOne();	//悔棋要两边同时返回棋子原来的位置
    backOne();

    QByteArray buf;
    buf.append(3);
    _socket->write(buf);	//再写数据进行发送
}

void NetGame::click(int id, int row, int col)
{
    if(_bRedTurn != _bSide)
        return;	//如果现在还没有轮到你下棋，则你不能执行悔棋操作

    Board::click(id, row, col);	//继承了board的函数click，获得点击的id 和该id的所在的行和列，

    /* 发送给对方 */
    QByteArray buf;
    buf.append(2);
    buf.append(id);
    buf.append(row);
    buf.append(col);
    _socket->write(buf);	//将这些数据发送给对方
}

/* 由于返回是两边同时金进行的，所以再调整的时候，就要一起调整整个框架 */
void NetGame::backFromNetwork(QByteArray)
{
    backOne();	
    backOne();
}

void NetGame::clickFromNetwork(QByteArray buf)
{
    Board::click(buf[1], 9-buf[2], 8-buf[3]);
}

/* 网络初始化 */
void NetGame::initFromNetwork(QByteArray buf)
{
    bool bRedSide = buf.at(1)>0?true:false;
    init(bRedSide);
}

/* 根据接受到的数据，采取各种措施来执行函数 */
void NetGame::slotDataArrive()
{
    QByteArray buf = _socket->readAll();
    switch (buf.at(0)) {
    case 1:
        initFromNetwork(buf);
        break;
    case 2:
        clickFromNetwork(buf);
        break;
    case 3:
        backFromNetwork(buf);
        break;
    default:
        break;
    }
}

NetGame::~NetGame()
{

}

