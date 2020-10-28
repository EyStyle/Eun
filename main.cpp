//#pragma execution_character_set("utf-8")

#include <QApplication>
#include "ChooseDlg.h"
#include "MainWnd.h"
#include "loginui.h"
#include <QTime>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QTime t = QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);

    LoginUI login;  //login window
    login.exec();

    ChooseDlg dlg;  //choose which type you want to play
    if(login.login_flag == 1)   //if login success then show the board
    {
        if(dlg.exec() != QDialog::Accepted)
        {
           return 0;
        }
        MainWnd wnd(dlg._selected);
        wnd.setMaximumSize(730,700);
        wnd.setMinimumSize(730,700);
        wnd.show();
        return app.exec();
    }
}
