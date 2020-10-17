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

    // Get all existing personages
    std::vector<int> personages = Eng->GetPersIds();

    std::vector<QPushButton*> pers;

    for(auto it = personages.begin(); it != personages.end(); ++it)
    {
        //  нопка с вшитым "ID" внутри
        QPushButton* butt = new QPushButton(QString::fromStdString(Eng->GetPersById(*it)->GetName()));
        butt->setProperty("pers_id", Eng->GetPersById(*it)->GetId());
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

    //ui->pushButton->setProperty("id",0);

    connect(ui->pushButton, &QPushButton::clicked, main_wind, &MainWindow::CreateTaskForm);

}

PersonageMenu::~PersonageMenu()
{
    delete ui;
}
