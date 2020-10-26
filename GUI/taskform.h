#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>
#include "../Core/engine.h"
#include <QTreeWidget>
#include "dialogs/skillcreatedialog.h"
#include "dialogs/taskcreatedialog.h"

class MainWindow;

namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskForm(Engine *engine, int char_id, MainWindow* main_wind, QWidget *parent = nullptr);

    void UpdateTasks();

    void UpdateSkillsBox();

    virtual ~TaskForm();

private slots:

    void on_comboboxSkills_activated(int index);

    void CreateSkill();

    void on_treeTasks_itemSelectionChanged();

    void TaskComplete(int id);
    // проверка на
    void on_treeTasks_itemClicked(QTreeWidgetItem *item, int column);


    void on_actionCreate_new_task_triggered();

    void on_actionEdit_Task_triggered();

    void on_actionDelete_Task_triggered();

private:

    Engine* Eng;
    int CharId;
    MainWindow* MainWind;

    Ui::TaskForm *ui;

    void CreateAboutChar();

    void UpdateSkillDesc();

    void CreateChilds(int task_id, QTreeWidgetItem* par);

};

#endif // TASKFORM_H
