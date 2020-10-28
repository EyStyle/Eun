#ifndef LOGINUI_H
#define LOGINUI_H
#include <QDialog>

namespace Ui
{
    class LoginUI;
}

class LoginUI : public QDialog
{
    Q_OBJECT

public:
    explicit LoginUI(QWidget *parent = 0);
     int login_flag = 0;//define flag which mark login success
    ~LoginUI();

private slots:

    void on_regist_clicked();

    void on_Login_clicked();

private:
    Ui::LoginUI *ui;
};

#endif // LOGINUI_H
