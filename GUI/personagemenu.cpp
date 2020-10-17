#include "personagemenu.h"
#include "ui_personagemenu.h"
#include "mainwindow.h"

PersonageMenu::PersonageMenu(Engine *engine, MainWindow* main_wind, QWidget *parent) :
    QWidget(parent),
    MainWind(main_wind),
    Eng(engine),
    ui(new Ui::PersonageMenu)
{
    ui->setupUi(this);

    UpdatePersGrid();
}

PersonageMenu::~PersonageMenu()
{
    delete ui;
}

void PersonageMenu::CreatePers()
{
    PersonCreateDialog* dialog = new PersonCreateDialog;
    if(dialog->exec() == QDialog::Accepted)
    {
        Eng->CreatePers(dialog->GetPersName(),dialog->GetPersDesc());
    }
    delete dialog;
    UpdatePersGrid();
}

void PersonageMenu::UpdatePersGrid()
{
    // Get all existing personages
    std::vector<int> personages = Eng->GetPersIds();

    // Creating buttons for personages
    std::vector<PersonageButton*> pers;
    for(auto it = personages.begin(); it != personages.end(); ++it)
    {
        // Button with "id" inside
        int id = Eng->GetPersById(*it)->GetId();
        std::string name = Eng->GetPersById(*it)->GetName();

        PersonageButton* butt = new PersonageButton(id, name);
        pers.push_back(butt);
    }

    // Fillng grid layout
    int col = 0;
    int row = 0;
    for(int it = 0; it < personages.size(); ++it)
    {
        ui->gridLayoutPers->addWidget(pers.at(it), row, col);
        col++;
        if(col == 3)
        {
            col = 0;
            row++;
        }
        connect(pers.at(it), &QPushButton::clicked, MainWind, &MainWindow::CreateTaskForm);
    }

    // Adding button for creating new personage
    QPushButton* add_pers = new QPushButton("+");

    if(col==0)
        col = 1;

    ui->gridLayoutPers->addWidget(add_pers, row, col);

    connect(add_pers, &QPushButton::clicked, this, &PersonageMenu::CreatePers);
}
