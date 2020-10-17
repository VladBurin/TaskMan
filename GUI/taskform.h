#ifndef TASKFORM_H
#define TASKFORM_H

#include <QWidget>
#include "../Core/engine.h"
#include <QTreeWidget>

class MainWindow;

namespace Ui {
class TaskForm;
}

class TaskForm : public QWidget
{
    Q_OBJECT

public:
    explicit TaskForm(Engine *engine, int pers_id, MainWindow* main_wind, QWidget *parent = nullptr);

    void RefreshTasks();

    ~TaskForm();

private slots:
    void on_comboBox_activated(int index);

    void on_pushButton_2_clicked();

private:

    Engine* Eng;
    int PersId;
    MainWindow* MainWind;

    Ui::TaskForm *ui;


    void CreateChilds(int task_id, QTreeWidgetItem* par);

};

#endif // TASKFORM_H
