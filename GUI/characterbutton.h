#ifndef PERSONAGEBUTTON_H
#define PERSONAGEBUTTON_H

#include <QPushButton>
#include <QAction>
//TODO create actions for edit character

class CharacterButton : public QPushButton
{
    Q_OBJECT
public:
    CharacterButton(int id, std::string name, QWidget *parent = nullptr);
    virtual ~CharacterButton();

    virtual void enterEvent(QEvent * event);
    virtual void leaveEvent(QEvent * event);

signals:
       void clicked(int id);

       void CharEnter(int id);

       void CharLeave();

       void DeleteChar(int id);

       void EditChar(int id);


private slots:
    void reemitClicked();

    void reemitEditChar();

    void reemitDelChar();

private:
    int CharId;
};

#endif // PERSONAGEBUTTON_H
