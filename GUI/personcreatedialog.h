#ifndef PERSONCREATEDIALOG_H
#define PERSONCREATEDIALOG_H

#include <QDialog>

namespace Ui {
class PersonCreateDialog;
}

class PersonCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PersonCreateDialog(QWidget *parent = nullptr);
    ~PersonCreateDialog();

private:
    Ui::PersonCreateDialog *ui;
};

#endif // PERSONCREATEDIALOG_H
