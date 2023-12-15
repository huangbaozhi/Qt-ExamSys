#ifndef EXAMDIALOG_H
#define EXAMDIALOG_H

#include <QDialog>
#include <QTimer>

class ExamDialog : public QDialog
{
    Q_OBJECT
public:
    ExamDialog(QWidget* parent = 0);
    void initTimer();

private:
    QTimer *m_timer;        // 计时器
    int m_timerGo;          // 考试已用时

private slots:
    void freshTime();
};

#endif // EXAMDIALOG_H
