#include "personagebutton.h"

PersonageButton::PersonageButton(int id, std::string name, QWidget *parent)
                : QPushButton(parent),
                  PersId(id)
{
    setText(name.c_str());
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));

    QAction *editPers = new QAction("Edit character");
    QAction *deletePers = new QAction("Delete character");

    this->addAction(editPers);
    this->addAction(deletePers);

    this->setContextMenuPolicy(Qt::ActionsContextMenu);


    connect(editPers,   &QAction::triggered, this, &PersonageButton::reemitEditPers);
    connect(deletePers, &QAction::triggered, this, &PersonageButton::reemitDelPers);

}

// TODO Edit person implement
PersonageButton::~PersonageButton()
{

}

void PersonageButton::enterEvent(QEvent * event)
{
    emit PersEnter(PersId);
}

void PersonageButton::leaveEvent(QEvent * event)
{
    emit PersLeave();
}

void PersonageButton::reemitClicked()
{
    emit clicked(PersId);
}

void PersonageButton::reemitEditPers()
{
    emit EditPersonage(PersId);
}

void PersonageButton::reemitDelPers()
{
    emit DeletePers(PersId);
}


