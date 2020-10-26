#ifndef PERSONCREATEDIALOG_H
#define PERSONCREATEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


class CharCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharCreateDialog(QWidget *parent = nullptr);
    ~CharCreateDialog();

    std::string GetPersName();
    std::string GetPersDesc();

private:
    QLabel* EnterNameLabel;
    QLineEdit* CharName;

    QLabel* EnterDescLabel;
    QTextEdit* CharDescript;

    QPushButton* OkButton;
    QPushButton* CancelButton;
};

#endif // PERSONCREATEDIALOG_H
