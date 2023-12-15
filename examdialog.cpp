#include "examdialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QApplication>
#include <QPalette>
#include <QFont>
#include <QColor>

ExamDialog::ExamDialog(QWidget* parent) : QDialog(parent)
{
    // 设置字体大小
    QFont font;
    font.setPointSize(12);
    this->setFont(font);

    // 设置窗体背景颜色
    setPalette(QPalette(QColor(209,215,255)));

    setWindowTitle("考试已用时：0分0秒");
    setWindowFlags(Qt::Dialog | Qt::WindowCloseButtonHint);
    resize(800,900);

    initTimer();
    initLayout();
    if(!initTextEdit()){
        QMessageBox::information(this,"提示","初始化题库数据文件失败！");
        QTimer::singleShot(0,qApp,SLOT(quit()));
    }
}

void ExamDialog::initTimer()
{
    m_timerGo = 0;//初试时间为0
    m_timer = new QTimer(this);
    m_timer->setInterval(1000); // 1000ms=1s
    m_timer->start();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(freshTime()));
}

void ExamDialog::initLayout()
{
    m_layout = new QGridLayout(this);
    m_layout->setSpacing(10);
    m_layout->setHorizontalSpacing(10);
    m_layout->setVerticalSpacing(10);
}

bool ExamDialog::initTextEdit()
{
    QString strLine;        // 保存文件中读取到的一行数据
    QStringList strList;    // 保存读取到的答案行
    QString fileName("/Users/huangbaozhi/Desktop/Qtcode/ExamSys/ExamSys/exam.txt");
    QFile file(fileName);
    QTextStream stream(&file);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_textEdit = new QTextEdit(this);
        m_textEdit->setReadOnly(true);
        QString strText;    // 用于保存显示到文本编辑器的数据
        int nLines = 0;
        while(!stream.atEnd()){

            // 过滤首行
            if(nLines == 0)
            {
                stream.readLine();
                nLines++;
                continue;
            }

            //过滤答案行
            if((nLines >= 6 && nLines <= 6 * 9 && (nLines % 6 == 0))    // 选择题
                || (nLines == 6 * 9 + 4))   // 判断题
            {
                strLine = stream.readLine();
                strList = strLine.split(" ");
                m_answerList.append(strList.at(1));
                strText += "\n";
                nLines++;
                continue;
            }

            strText += stream.readLine();
            strText += "\n";
            nLines++;
        }
        m_textEdit->setText(strText);
        m_layout->addWidget(m_textEdit,0,0,1,10);
        file.close();
        return true;
    }else{
        return false;
    }
}

void ExamDialog::freshTime()
{
    m_timerGo++;  // 刷新考试用时
    // 计算分钟
    QString min = QString::number(m_timerGo / 60);
    QString sec = QString::number(m_timerGo % 60);
    setWindowTitle("考试已用时：" + min + "分" +sec + "秒");
}
