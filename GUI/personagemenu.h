#ifndef PERSONAGEMENU_H
#define PERSONAGEMENU_H

#include <QWidget>
#include <QPushButton>
#include "../Core/engine.h"

#include "personagebutton.h"
#include "personcreatedialog.h"
class MainWindow;



namespace Ui {
class PersonageMenu;
}

class PersonageMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PersonageMenu(Engine *engine, MainWindow* main_wind, QWidget *parent = nullptr);
    ~PersonageMenu();

    void UpdatePersGrid();

public slots:
    void CreatePers();
    //void DeletePers();
    //void EditPers();



private:
    Engine* Eng;
    MainWindow* MainWind;
    Ui::PersonageMenu *ui;
};

#endif // PERSONAGEMENU_H
