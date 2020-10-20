#include "personagemenu.h"
#include "ui_personagemenu.h"
#include "mainwindow.h"

PersonageMenu::PersonageMenu(Engine *engine, MainWindow* main_wind, QWidget *parent) :
    QWidget(parent),
    Eng(engine),
    MainWind(main_wind),
    createPers(nullptr),
    ui(new Ui::PersonageMenu)
{
    ui->setupUi(this);

    UpdatePersGrid();

    connect(ui->actionCreate_New_Pers, &QAction::triggered, this, &PersonageMenu::CreatePers);
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

void PersonageMenu::ClearAboutPers()
{
    ui->textDescription->clear();
}

void PersonageMenu::UpdateAboutPers(int id)
{
    ui->textDescription->clear();

    Personage* pers = Eng->GetPersById(id);

    std::string name = pers->GetName();
    std::string descript = pers->GetDescript();
    int level = pers->GetLevel();
    int score_sum = pers->GetScoresSum();

    QString text;
    text += "Name: \t\t" +QString::fromStdString(name) + "\n";
    text += "Description: \t" +QString::fromStdString(descript) + "\n";
    text += "Level: \t\t" +QString::number(level) + "\n";
    text += "Sum of score: \t" +QString::number(score_sum) + "\n";

    ui->textDescription->setText(text);

}

void PersonageMenu::UpdatePersGrid()
{
    // TODO очистка и удаление всех виджетов (попытка удаления КНОПКА пока ее слот ещё выполняется)
//    if(createPers)
//        delete createPers;

//    for(auto it = Pers.begin(); it != Pers.end(); ++it)
//    {
//        delete (*it);
//    }

    // Get all existing personages
    std::vector<int> personages = Eng->GetPersIds();

    // Creating buttons for personages
    Pers.clear();
    for(auto it = personages.begin(); it != personages.end(); ++it)
    {
        // Button with "id" inside
        int id = Eng->GetPersById(*it)->GetId();
        std::string name = Eng->GetPersById(*it)->GetName();

        PersonageButton* butt = new PersonageButton(id, name);
        Pers.push_back(butt);
    }

    // Fillng grid layout
    int col = 0;
    int row = 0;
    for(int it = 0; it < personages.size(); ++it)
    {
        ui->gridLayoutPers->addWidget(Pers.at(it), row, col);
        col++;
        if(col == 3)
        {
            col = 0;
            row++;
        }

        connect(Pers.at(it), &PersonageButton::clicked, MainWind, &MainWindow::CreateTaskForm);
        connect(Pers.at(it), &PersonageButton::PersEnter, this, &PersonageMenu::UpdateAboutPers);
        connect(Pers.at(it), &PersonageButton::PersLeave, this, &PersonageMenu::ClearAboutPers);

        connect(Pers.at(it), &PersonageButton::EditPersonage, this, &PersonageMenu::EditPers);
        connect(Pers.at(it), &PersonageButton::DeletePers, this, &PersonageMenu::DeletePers);
    }

    // Adding button for creating new personage
    createPers = new QPushButton("+");

    if(col==0)
        col = 1;

    ui->gridLayoutPers->addWidget(createPers, row, col);

    connect(createPers, &QPushButton::clicked, this, &PersonageMenu::CreatePers);
}

void PersonageMenu::DeletePers(int id)
{
    DelPersDialog* dialog = new DelPersDialog(Eng->GetPersById(id)->GetName());

    if(dialog->exec() == QDialog::Accepted)
    {
        Eng->DeletePers(id);
    }

    delete dialog;

    UpdatePersGrid();
}

void PersonageMenu::EditPers(int id)
{
    // диалог
}
