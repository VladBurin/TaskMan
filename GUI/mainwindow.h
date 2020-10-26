#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Core/engine.h"

#include "charactermenu.h"
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
        void CreateCharForm();

private:
    Ui::MainWindow *ui;

    //Engine
    Engine* Eng;
    // возможные варианты центрального виджета
    CharacterMenu* CharMenu;
    TaskForm* TaskFormIns;

};

#endif // MAINWINDOW_H
