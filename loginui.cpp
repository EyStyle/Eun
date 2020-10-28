#include "loginui.h"
#include "ui_loginui.h"
#include <QMessageBox>
#include <string>
#include <iostream>
#include <fstream>
#include <QDebug>
using namespace std;

LoginUI::LoginUI(QWidget *parent) :QDialog(parent),ui(new Ui::LoginUI)
{
    ui->setupUi(this);
    this->setMaximumSize(360,160); //setting the size of this ligin window
    this->setMinimumSize(360,160);
    ui->AccountLineEdit->setPlaceholderText("Please input your Account");
    ui->PasswdlineEdit->setPlaceholderText("please input your Passwd");
    ui->PasswdlineEdit->setEchoMode(QLineEdit::Password);
    ui->AccountLineEdit->setText("majun");
    ui->PasswdlineEdit->setText("majun");
}

void LoginUI::on_regist_clicked()
{
    string usrname = ui->AccountLineEdit->text().toStdString();
    string psword = ui->PasswdlineEdit->text().toStdString();
    string temp;
    int i = 0;
    int Have_name_flag = 0;
    ifstream fin("../Chinese_cheese/UsrInfo.txt", ios::in);//在这个路径下读入文件
    ofstream fout("../Chinese_cheese/UsrInfo.txt", ios::app);//在同一个路径下，如果注册成功则写入文件
    temp = usrname; //先吧名字读进去
    while (std::getline(fin, temp))//每次读一行的数据进入temp中。
    {
        i++;
        if (i % 2 == 0) continue;//访问的是密码这一行，跳出。
        if (usrname == temp.c_str())
        {
            Have_name_flag = 1;
            break;
        }
        else
        {
            Have_name_flag =0;
        }
    }
    if(Have_name_flag == 1)
    {
        this->ui->AccountLineEdit->clear();
        this->ui->PasswdlineEdit->clear();
        this->ui->AccountLineEdit->setFocus();
        QMessageBox::warning(this,tr("warning"),tr(" Name Exist ,Please again!"),QMessageBox::Yes);
    }
    else
    {
        fout << usrname << endl;//向文件写入注册者的用户名，然后换一行
        fout << psword << endl<<endl<<endl;//写入密码，换行
        fout.close();
        QMessageBox::warning(this,tr("warning"),tr(" Register Success!"),QMessageBox::Yes);
    }
    fin.close();
}

void LoginUI::on_Login_clicked()
{
    string usrname = ui->AccountLineEdit->text().toStdString();
    string psword = ui->PasswdlineEdit->text().toStdString();
    string temp1;
    string temp2;
    int i=0;
    int No_name_flag = 0;//定义一个标志，如果没有用户名，则值为1
    ifstream fin("../Chinese_cheese/UsrInfo.txt", ios::in);
    if(ui->AccountLineEdit->text()=="") //Check AccountLineEdit whether empty
    {
        QMessageBox::warning(this,tr("Warning"),tr("Please Input Account  !"),QMessageBox::Yes);
        this->ui->PasswdlineEdit->clear();
        this->ui->AccountLineEdit->setFocus();
       return;
    }
    while (std::getline(fin, temp1))
    {
        std::getline(fin, temp2);//一次读进去两行，分别是用户名和密码
        if (usrname != temp1.c_str())//有这个用户名了，接下来看看密码是不是相符的
        {
            No_name_flag = 1;
        }
        else
        {
            if ((i % 2) == 0 && psword == temp2.c_str())//相符
            {
                this->close();
                login_flag = 1;
                No_name_flag = 0;            
                break;
            }
            else
            {
                QMessageBox::warning(this,tr("warning"),tr("passwd error !"),QMessageBox::Yes);
                this->ui->PasswdlineEdit->clear();
                this->ui->AccountLineEdit->setFocus();
                No_name_flag = 0;
                break;
            }

        }
    }
    if(No_name_flag == 1)
    {
       QMessageBox::warning(this,tr("warning"),tr("Do Not Exist ,Please Register!"),QMessageBox::Yes);
    }
    fin.close();
}

LoginUI::~LoginUI()
{
    delete ui;
}
