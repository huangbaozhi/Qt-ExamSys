#include "examdialog.h"

ExamDialog::ExamDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("考试已用时：0分0秒");
    initTimer();
}

void ExamDialog::initTimer()
{
    m_timerGo = 0;
    m_timer = new QTimer(this);
    m_timer->setInterval(1000); // 1000ms=1s
    m_timer->start();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(freshTime()));
}

void ExamDialog::freshTime()
{
    m_timerGo++;  // 刷新考试用时
    // 计算分钟
    QString min = QString::number(m_timerGo / 60);
    QString sec = QString::number(m_timerGo % 60);
    setWindowTitle("考试已用时：" + min + "分" +sec + "秒");
}
