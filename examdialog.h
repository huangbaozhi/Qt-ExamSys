#ifndef EXAMDIALOG_H
#define EXAMDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QTextEdit>
#include <QLabel>
#include <QRadioButton>
#include <QCheckBox>
#include <QGridLayout>
#include <QStringList>
#include <QButtonGroup>

class ExamDialog : public QDialog
{
    Q_OBJECT
public:
    ExamDialog(QWidget* parent = 0);
    void initTimer();       // 初始化计时器
    void initLayout();      // 初始化布局管理器
    bool initTextEdit();    // 初始化文本编辑器
    void initButtons();     // 初始化按钮及标签
private:
    QTimer *m_timer;        // 计时器
    int m_timerGo;          // 考试已用时

    QTextEdit *m_textEdit;  // 考试题库显示
    QLabel *m_titleLables[10];  // 题目标签
    QButtonGroup *m_btnGroups[9];   // 单选按钮分组
    QRadioButton *m_radioBtns[32];  // 单选题按钮
    QCheckBox *m_checkBtns[4];      // 多选按钮
    QRadioButton *m_radioA;         // 判断题A选项
    QRadioButton *m_radioB;         // 判断题B选项
    QGridLayout *m_layout;          // 布局管理器
    QStringList m_answerList;       // 答案的链表
private slots:
    void freshTime();
};

#endif // EXAMDIALOG_H
