#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(Engine *engine, QWidget *parent) :
    Eng(engine),
    QMainWindow(parent),
    CharMenu(nullptr),
    TaskFormIns(nullptr),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CharMenu = new CharacterMenu(Eng,this);
    setCentralWidget(CharMenu);
    this->setWindowTitle("Characters");
    this->resize(1000,600);
}

void MainWindow::CreateTaskForm(int id)
{
    delete CharMenu;
    TaskFormIns = new TaskForm(Eng,id,this);

    setCentralWidget(TaskFormIns);
    this->setWindowTitle("Tasks");
}

void MainWindow::CreateCharForm()
{
    delete TaskFormIns;
    CharMenu = new CharacterMenu(Eng,this);

    setCentralWidget(CharMenu);
    this->setWindowTitle("Characters");
}

MainWindow::~MainWindow()
{
    delete ui;
}
