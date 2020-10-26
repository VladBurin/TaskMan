#ifndef DELPERSDIALOG_H
#define DELPERSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>


class DelCharDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DelCharDialog(std::string pers_name, QWidget *parent = nullptr);
    ~DelCharDialog();

private:

    QLabel* Massage;


    QPushButton* OkButton;
    QPushButton* CancelButton;
};

#endif // DELPERSDIALOG_H
