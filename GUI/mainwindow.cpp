#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Engine *engine, QWidget *parent) :
    Eng(engine),
    QMainWindow(parent),
    PersMenu(nullptr),
    TaskFormIns(nullptr),
    ui(new Ui::MainWindow)
{
    MainWindow* g = this;
    //TaskForm *w = new TaskForm(MainEngine,0);

    PersMenu = new PersonageMenu(Eng,this);

    setCentralWidget(PersMenu);

    this->resize(300,500);
}

void MainWindow::CreateTaskForm(int id)
{
    delete PersMenu;
    id = 0;
    TaskFormIns = new TaskForm(Eng,id,this);

    setCentralWidget(TaskFormIns);
}

void MainWindow::CreatePersForm()
{
    delete TaskFormIns;
    PersMenu = new PersonageMenu(Eng,this);

    setCentralWidget(PersMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}
