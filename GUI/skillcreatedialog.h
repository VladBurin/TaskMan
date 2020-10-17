#ifndef SKILLCREATEDIALOG_H
#define SKILLCREATEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class SkillCreateDIalog : public QDialog
{
    Q_OBJECT

public:
    explicit SkillCreateDIalog(QWidget *parent = nullptr);
    ~SkillCreateDIalog();

private:
    QLabel* EnterNameLabel;
    QLineEdit* SkillName;

    QLabel* EnterDescLabel;
    QTextEdit* SkillDescript;

    QPushButton* OkButton;
    QPushButton* CancelButton;
};

#endif // SKILLCREATEDIALOG_H
