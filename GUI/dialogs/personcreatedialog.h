#ifndef PERSONCREATEDIALOG_H
#define PERSONCREATEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


class PersonCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PersonCreateDialog(QWidget *parent = nullptr);
    ~PersonCreateDialog();

    std::string GetPersName();
    std::string GetPersDesc();

private:
    QLabel* EnterNameLabel;
    QLineEdit* PersName;

    QLabel* EnterDescLabel;
    QTextEdit* PersDescript;

    QPushButton* OkButton;
    QPushButton* CancelButton;
};

#endif // PERSONCREATEDIALOG_H
