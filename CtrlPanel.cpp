#include "CtrlPanel.h"
#include <QGridLayout>
#include <QVBoxLayout>
CtrlPanel::CtrlPanel(QWidget *parent) : QWidget(parent)
{
    QGridLayout* grid = new QGridLayout(this);
    QVBoxLayout* vLay = new QVBoxLayout;
    window()->setStyleSheet(QStringLiteral("background-color: rgb(93, 159, 207);"));    //set background-color

//    grid->setColumnStretch(0, 1);
//    grid->setColumnStretch(2, 1);
//    grid->setRowStretch(0, 1);
    grid->setRowStretch(2, 1);
    grid->addLayout(vLay, 1, 1);

    vLay->addWidget(this->_back = new QPushButton("悔 棋"));

    connect(this->_back, SIGNAL(clicked()), this, SIGNAL(sigBack()));
}

CtrlPanel::~CtrlPanel()
{

}

