#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Engine *engine, QWidget *parent) :
    Eng(engine),
    QMainWindow(parent),
    PersMenu(nullptr),
    TaskFormIns(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PersMenu = new PersonageMenu(Eng,this);
    setCentralWidget(PersMenu);
    this->setWindowTitle("Characters");
    this->resize(500,400);
}

void MainWindow::CreateTaskForm(int id)
{
    delete PersMenu;
    TaskFormIns = new TaskForm(Eng,id,this);

    setCentralWidget(TaskFormIns);
    this->setWindowTitle("Tasks");
}

void MainWindow::CreatePersForm()
{
    delete TaskFormIns;
    PersMenu = new PersonageMenu(Eng,this);

    setCentralWidget(PersMenu);
    this->setWindowTitle("Characters");
}

MainWindow::~MainWindow()
{
    delete ui;
}
