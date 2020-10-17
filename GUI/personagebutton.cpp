#include "personagebutton.h"

PersonageButton::PersonageButton(int id, std::string name, QWidget *parent)
                : QPushButton(parent),
                  PersId(id)
{
    setText(name.c_str());
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

PersonageButton::~PersonageButton()
{

}

void PersonageButton::reemitClicked()
{
    emit clicked(PersId);
}


