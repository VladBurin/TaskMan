#ifndef TASKCREATEDIALOG_H
#define TASKCREATEDIALOG_H

#include <QDialog>

namespace Ui {
class TaskCreateDialog;
}

class TaskCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskCreateDialog(QWidget *parent = nullptr);
    ~TaskCreateDialog();

private:
    Ui::TaskCreateDialog *ui;
};

#endif // TASKCREATEDIALOG_H
