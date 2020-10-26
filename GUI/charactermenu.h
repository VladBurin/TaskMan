#ifndef CharacterMenu_H
#define CharacterMenu_H

#include <QWidget>
#include <QPushButton>
#include "../Core/engine.h"

#include "characterbutton.h"
#include "dialogs/charactercreatedialog.h"
//#include "dialogs/editchardialog.h"
#include "dialogs/delchardialog.h"

class MainWindow;


namespace Ui {
class CharacterMenu;
}

class CharacterMenu : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterMenu(Engine *engine, MainWindow* main_wind, QWidget *parent = nullptr);
    virtual ~CharacterMenu();

    void UpdateCharsGrid();

public slots:
    void CreateChar();

    void DeleteChar(int id);
    void EditChar(int id);

    void ClearAboutChars();
    void UpdateAboutChars(int id);



private:
    Engine* Eng;
    MainWindow* MainWind;
    Ui::CharacterMenu *ui;

    std::vector<CharacterButton*> Chars;
    QPushButton* createChar;
};

#endif // CharacterMenu_H
