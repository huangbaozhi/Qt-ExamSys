#include "logindialog.h"
#include "examdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog logDialog;
    int res = logDialog.exec();// 模态窗口运行
    if(res == QDialog::Accepted)
    {
        ExamDialog *examDialog;
        examDialog = new ExamDialog;
    }else
    {
        return 0;
    }
    return a.exec();    // 生命周期
}
