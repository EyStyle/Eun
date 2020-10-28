#ifndef NETGAME_H
#define NETGAME_H

#include "Board.h"
#include <QTcpServer>
#include <QTcpSocket>

/*
 * 报文格式定义
 * 1.初始化    两个字节
 * 2.鼠标点击   四个字节
 * 3.悔棋      一个字节
 *
*/

class NetGame : public Board	//继承了Board的一些函数
{
    Q_OBJECT
public:
    explicit NetGame(bool server, QWidget *parent = 0);
    ~NetGame();

    bool _bServer;	//声明是服务端还是客服端
    QTcpServer* _server;	//声明server和socket
    QTcpSocket* _socket;

    void back();	//声明返回一部操作
    void click(int id, int row, int col);	//声明点击操作

    void backFromNetwork(QByteArray buf);	//声明相应的网络返回函数
    void clickFromNetwork(QByteArray buf);	//声明网络点击函数
    void initFromNetwork(QByteArray buf);	//声明初始化网络函数

signals:

public slots:
    void slotNewConnection();	//声明对应的槽，这里是新的连接槽函数
    void slotDataArrive();	//声明数据到来后的槽函数
};

#endif // NETGAME_H
