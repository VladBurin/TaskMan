#ifndef TASKCREATEDIALOG_H
#define TASKCREATEDIALOG_H

#include <QDialog>
#include "../../Core/engine.h"

namespace Ui {
class TaskCreateDialog;
}

class TaskCreateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TaskCreateDialog(Engine *engine, int char_id, int init_skill_id, int init_task_id = -11, QWidget *parent = nullptr);
    ~TaskCreateDialog();

    int GetSkillId();
    int GetParentTaskId();
    std::string GetTaskName();
    std::string GetTaskDesc();
    int GetTaskScore();

private slots:
    void on_comboBoxSkillChoice_currentIndexChanged(const QString &arg1);

private:
    Ui::TaskCreateDialog *ui;

    int CharId;

    Engine* Eng;

    void UpdateParentTaskBox(int skill_id);
};

#endif // TASKCREATEDIALOG_H
