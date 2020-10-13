#ifndef PERSONAGEMENU_H
#define PERSONAGEMENU_H

#include <QWidget>
#include <QPushButton>
#include "../Core/engine.h"

namespace Ui {
class PersonageMenu;
}

class PersonageMenu : public QWidget
{
    Q_OBJECT

public:
    explicit PersonageMenu(Engine *engine, QWidget *parent = nullptr);
    ~PersonageMenu();

private:
    Engine* Engine_instance;
    Ui::PersonageMenu *ui;
};

#endif // PERSONAGEMENU_H
