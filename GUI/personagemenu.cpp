#include "personagemenu.h"
#include "ui_personagemenu.h"

PersonageMenu::PersonageMenu(Engine *engine, QWidget *parent) :
    Engine_instance(engine),
    QWidget(parent),
    ui(new Ui::PersonageMenu)
{
    ui->setupUi(this);

    std::vector<int> personages = Engine_instance->GetPersIds();

    std::vector<QPushButton*> pers;

    for(auto it = personages.begin(); it != personages.end(); ++it)
    {
        QPushButton* butt = new QPushButton(QString::fromStdString(Engine_instance->GetPersById(*it)->GetName()));
        pers.push_back(butt);
    }

    ui->gridLayout->setMargin(5);
    ui->gridLayout->setSpacing(15);


    int col = 0;
    int row = 0;
    for(int it = 0; it < personages.size(); ++it)
    {
        ui->gridLayout->addWidget(pers.at(it), row, col);
        col++;
        if(col == 3)
        {
            col = 0;
            row++;
        }
    }



}

PersonageMenu::~PersonageMenu()
{
    delete ui;
}
