#ifndef PERSONAGEMENU_H
#define PERSONAGEMENU_H

#include <QWidget>
#include <QPushButton>
#include "../Core/engine.h"

#include "personagebutton.h"
#include "dialogs/personcreatedialog.h"
//#include "dialogs/editpersdialog.h"
#include "dialogs/delpersdialog.h"

class MainWindow;



namespace Ui {
class PersonageMenu;
}

class PersonageMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PersonageMenu(Engine *engine, MainWindow* main_wind, QWidget *parent = nullptr);
    virtual ~PersonageMenu();

    void UpdatePersGrid();

public slots:
    void CreatePers();

    void DeletePers(int id);
    void EditPers(int id);

    void ClearAboutPers();
    void UpdateAboutPers(int id);



private:
    Engine* Eng;
    MainWindow* MainWind;
    Ui::PersonageMenu *ui;

    std::vector<PersonageButton*> Pers;
    QPushButton* createPers;
};

#endif // PERSONAGEMENU_H
