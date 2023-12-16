#include "logindialog.h"
#include "ui_logindialog.h"

#include <QMessageBox>
#include <QRegExp>
#include <QFile>
#include <QTextStream>
#include <QDebug>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setFixedSize(width(),height());
    this->setWindowTitle("驾校科目一考试登录");
    this->setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}


void LoginDialog::on_loginBtn_clicked()
{
    //QMessageBox::information(this, "提示", "槽方法调用啦！");

    // 正则验证邮箱地址 用户名@域名 653975671@qq.com
    // 表示符解释：^表示规则字符串的开始 $表示规则字符串的结束
    // +表示匹配次数>=1次 *表示匹配任意次数(可为0次） {n,m}表示匹配次数至少n次，至多m次

    // 验证邮箱地址，验证邮箱
    QRegExp rx("^[A-Za-z0-9]+([_\.][A-Za-z0-9]+)*@([A-Za-z0-9\-]+\.)+[A-Za-z]{2,6}$");
    bool res = rx.exactMatch(ui->accountEdit->text());

    if(!res) // 匹配不成功
    {
        QMessageBox::information(this, "提示", "非法的邮箱地址，请你重新输入!");
        ui->accountEdit->clear();
        ui->codeEdit->clear();
        ui->accountEdit->setFocus();
    }
    else
    {
        //QMessageBox::information(this, "提示", "欢迎登录科目一考试系统!");
        QString filename;           // 账号密码数据文件
        QString strAccInput;        // 用户输入的账号
        QString strCode;            // 用户输入的密码
        QString strLine;            // 每次读取的一行数据
        QStringList strList;        // 保存分割读取的一行数据

        //filename = "../account.txt";
        filename = "account.txt";
        strAccInput = ui->accountEdit->text();
        strCode = ui->codeEdit->text();

        QFile file(filename);
        QTextStream stream(&file);
        qDebug()<<"[文件路径 ]= "<<filename;
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            while(!stream.atEnd()){
            strLine = stream.readLine();
            strList = strLine.split(",");
            qDebug()<<"[账号]= "<<strList.at(0);
            qDebug()<<"[密码]= "<<strList.at(1);
            if(strAccInput == strList.at(0))    // 账号匹配成功
                if(strCode == strList.at(1))    // 密码匹配成功
                {
                    QMessageBox::information(this,"提示","欢迎进入科目一考试系统！");
                    file.close();
                    done(Accepted);// 关闭当前窗体，以指定方式返还
                    return;
                }else{
                    QMessageBox::information(this,"提示","您输入的密码有误，请重新输入！");
                    ui->codeEdit->clear();
                    ui->codeEdit->setFocus();
                    file.close();
                    return;
                }
            }

            QMessageBox::information(this,"提示","您输入的账号有误，请重新输入11！");
            ui->accountEdit->clear();
            ui->codeEdit->clear();
            ui->accountEdit->setFocus();
            file.close();
            return;
        }
        else
        {
            QMessageBox::information(this,"提示","读取账号数据文件失败！");
            return;
        }
    }
}


void LoginDialog::on_cancelBtn_clicked()
{
    done(Rejected);
}

