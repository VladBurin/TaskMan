#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Core/engine.h"

#include "personagemenu.h"
#include "taskform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Engine *engine, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
        void CreateTaskForm(int id);
        void CreatePersForm();

private:
    Ui::MainWindow *ui;

    //Engine
    Engine* Eng;
    // возможные варианты центрального виджета
    PersonageMenu* PersMenu;
    TaskForm* TaskFormIns;

};

#endif // MAINWINDOW_H
