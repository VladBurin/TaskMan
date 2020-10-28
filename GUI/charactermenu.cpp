#include "charactermenu.h"
#include "ui_charactermenu.h"
#include "mainwindow.h"

CharacterMenu::CharacterMenu(Engine *engine, MainWindow* main_wind, QWidget *parent) :
    QWidget(parent),
    Eng(engine),
    MainWind(main_wind),
    createChar(nullptr),
    ui(new Ui::CharacterMenu)
{
    ui->setupUi(this);

    UpdateCharsGrid();

    connect(ui->actionCreate_New_Pers, &QAction::triggered, this, &CharacterMenu::CreateChar);
}

CharacterMenu::~CharacterMenu()
{
    delete ui;
}

void CharacterMenu::CreateChar()
{
    CharCreateDialog* dialog = new CharCreateDialog;
    if(dialog->exec() == QDialog::Accepted)
    {
        Eng->CreateChar(dialog->GetPersName(),dialog->GetPersDesc());
    }
    delete dialog;
    UpdateCharsGrid();
}

void CharacterMenu::ClearAboutChars()
{
    ui->textDescription->clear();
}

void CharacterMenu::UpdateAboutChars(int id)
{
    ui->textDescription->clear();

    Character* pers = Eng->GetCharById(id);
    if(!pers)
        return;
    std::string name = pers->GetName();
    std::string descript = pers->GetDescript();
    int level = pers->GetLevel();
    int current_score = pers->GetCurrentLevelScore();
    int score_for_next_lev = pers->GetScoresToNextLevel();

    QString text;
    text += "Name: \t\t" + QString::fromStdString(name) + "\n";
    text += "Description: \t" + QString::fromStdString(descript) + "\n";
    text += "Level: \t\t" + QString::number(level) + "\n";
    text += "Score: \t" + QString::number(current_score) + " / " + QString::number(score_for_next_lev) + "\n";

    ui->textDescription->setText(text);

}

void CharacterMenu::UpdateCharsGrid()
{
    // TODO очистка и удаление всех виджетов (попытка удаления КНОПКИ пока ее слот ещё выполняется)
//    if(createPers)
//        delete createPers;

//    for(auto it = Pers.begin(); it != Pers.end(); ++it)
//    {
//        delete (*it);
//    }

    // Get all existing personages
    std::vector<int> personages = Eng->GetPersIds();

    // Creating buttons for personages
    Chars.clear();
    for(auto it = personages.begin(); it != personages.end(); ++it)
    {
        // Button with "id" inside
        int id = Eng->GetCharById(*it)->GetId();
        std::string name = Eng->GetCharById(*it)->GetName();

        CharacterButton* butt = new CharacterButton(id, name);
        Chars.push_back(butt);
    }

    // Fillng grid layout
    int col = 0;
    int row = 0;
    for(int it = 0; it < personages.size(); ++it)
    {
        ui->gridLayoutPers->addWidget(Chars.at(it), row, col);
        col++;
        if(col == 3)
        {
            col = 0;
            row++;
        }

        connect(Chars.at(it), &CharacterButton::clicked, MainWind, &MainWindow::CreateTaskForm);
        connect(Chars.at(it), &CharacterButton::CharEnter, this, &CharacterMenu::UpdateAboutChars);
        connect(Chars.at(it), &CharacterButton::CharLeave, this, &CharacterMenu::ClearAboutChars);

        connect(Chars.at(it), &CharacterButton::EditChar, this, &CharacterMenu::EditChar);
        connect(Chars.at(it), &CharacterButton::DeleteChar, this, &CharacterMenu::DeleteChar);
    }

    // Adding button for creating new Character
    createChar = new QPushButton("+");

    if(col==0)
        col = 1;

    ui->gridLayoutPers->addWidget(createChar, row, col);

    connect(createChar, &QPushButton::clicked, this, &CharacterMenu::CreateChar);
}

void CharacterMenu::DeleteChar(int id)
{
    DelCharDialog* dialog = new DelCharDialog(Eng->GetCharById(id)->GetName());

    if(dialog->exec() == QDialog::Accepted)
    {
        Eng->DeleteChar(id);
    }

    delete dialog;

    UpdateCharsGrid();
}

void CharacterMenu::EditChar(int id)
{
    // диалог
}
