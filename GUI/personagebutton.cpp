#include "personagebutton.h"

PersonageButton::PersonageButton(int digit, QWidget *parent)
                : QPushButton(parent)
{
    PersId = digit;
    setText(QString::number(PersId));
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));
}

PersonageButton::~PersonageButton()
{
}

void PersonageButton::reemitClicked()
{
    emit clicked(PersId);
}


