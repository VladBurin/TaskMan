#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>
#include "../Core/engine.h"
#include <QTreeWidget>
#include "dialogs/skillcreatedialog.h"

class MainWindow;

namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskForm(Engine *engine, int pers_id, MainWindow* main_wind, QWidget *parent = nullptr);

    void UpdateTasks();

    void UpdateSkillsBox();

    virtual ~TaskForm();

private slots:

    void on_comboboxSkills_activated(int index);

    void CreateSkill();
    void on_treeTasks_itemSelectionChanged();

private:

    Engine* Eng;
    int PersId;
    MainWindow* MainWind;

    Ui::TaskForm *ui;

    void CreateAboutPers();

    void UpdateSkillDesc();

    void CreateChilds(int task_id, QTreeWidgetItem* par);

};

#endif // TASKFORM_H
