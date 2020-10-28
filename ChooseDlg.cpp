#include "ChooseDlg.h"
#include <QVBoxLayout>
//选择对话框
ChooseDlg::ChooseDlg(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout* lay = new QVBoxLayout(this);//create a new layout
    window()->setLayout(lay);
    window()->setWindowTitle("choose mode");
    //resize this layout size
    setMaximumSize(150,150);
    setMinimumSize(150,150);
    window()->setStyleSheet(QStringLiteral("background-color: rgb(93, 159, 207);"));    //set background-color
    window()->show();
    lay->addWidget(_buttons[0] = new QPushButton("人机对战"));
    lay->addWidget(_buttons[1] = new QPushButton("人人对战"));
    lay->addWidget(_buttons[2] = new QPushButton("网络对战(服务端)"));
    lay->addWidget(_buttons[3] = new QPushButton("网络对战(客户端)"));

    for(int i=0; i<4; ++i)
    {
        connect(_buttons[i], SIGNAL(clicked()), this, SLOT(slotClicked()));
    }
}

//按键选择槽函数
void ChooseDlg::slotClicked()
{
    QObject* s = sender();
    for(int i=0; i<4; ++i)
    {
        if(_buttons[i] == s)
        {
            this->_selected = i;
            break;
        }
    }
    accept();
}

ChooseDlg::~ChooseDlg()
{

}

