#ifndef SKILLCREATEDIALOG_H
#define SKILLCREATEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class SkillCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SkillCreateDialog(QWidget *parent = nullptr);
    ~SkillCreateDialog();

    std::string GetPersName();
    std::string GetPersDesc();

private:
    QLabel* EnterNameLabel;
    QLineEdit* SkillName;

    QLabel* EnterDescLabel;
    QTextEdit* SkillDescript;

    QPushButton* OkButton;
    QPushButton* CancelButton;
};

#endif // SKILLCREATEDIALOG_H
