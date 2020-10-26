#include "characterbutton.h"

CharacterButton::CharacterButton(int id, std::string name, QWidget *parent)
                : QPushButton(parent),
                  CharId(id)
{
    setText(name.c_str());
    connect(this, SIGNAL(clicked()), this, SLOT(reemitClicked()));

    QAction *editChar = new QAction("Edit character");
    QAction *deleteChar = new QAction("Delete character");

    this->addAction(editChar);
    this->addAction(deleteChar);

    this->setContextMenuPolicy(Qt::ActionsContextMenu);


    connect(editChar,   &QAction::triggered, this, &CharacterButton::reemitEditChar);
    connect(deleteChar, &QAction::triggered, this, &CharacterButton::reemitDelChar);

}

// TODO Edit Charon implement
CharacterButton::~CharacterButton()
{

}

void CharacterButton::enterEvent(QEvent * event)
{
    emit CharEnter(CharId);
}

void CharacterButton::leaveEvent(QEvent * event)
{
    emit CharLeave();
}

void CharacterButton::reemitClicked()
{
    emit clicked(CharId);
}

void CharacterButton::reemitEditChar()
{
    emit EditChar(CharId);
}

void CharacterButton::reemitDelChar()
{
    emit DeleteChar(CharId);
}


